#include <iostream>
#include <future>
#include "threadpool.h"
#include <string>

// windows socket头文件
// 配置文件 tasks.json -> args中加入 "-lwsock32"
#include <winsock2.h>
#include <windows.h>
#pragma commet(lib, "ws2_32.lib")

#define SERVER_PORT 8888  	// 服务器端口号
#define BUFFER_SIZE 1024  	// 发送和接收文字的大小
#define MAX_CONNECT 2		// 可同时连接的服务器个数

std::vector<SOCKET> clientSocket;	// 存放当前连接服务器的套接字
std::mutex cs_mutex_;				// 互斥锁 保护 clientSocket
std::condition_variable cs_cond;	// 条件变量 保护 clientSocket

void conn_tips(SOCKET socket, SOCKADDR_IN *addr);
void chat_sock(int socket, SOCKADDR_IN *addr);
void conn_sock(SOCKET serverSocket, Threadpool* pool);

int main()
{

// 线性池
	Threadpool pool;
	pool.setMood(PoolMode::MOOD_FIXED);
	pool.start(4);

// 套接字库初始化
	// 确定网络协议版本。
	WSADATA wsadata;
	WORD w_req = MAKEWORD(2, 2); // 版本号
	int err = WSAStartup(w_req, &wsadata);
	if(err != 0)
	{
		std::cout << "套接字初始化失败！！！" << std::endl;
		return -1;
	}
	std::cout << "套接字初始化成功" << std::endl;

	// 检测版本号
	if(LOBYTE(wsadata.wVersion) != 2 ||
	   HIBYTE(wsadata.wHighVersion) != 2)
	   {
			std::cout << "套接字库版本不符！！" << GetLastError() << std::endl;
	   		return -1;
	   }
	std::cout << "套接字库版本正确" << std::endl;

// 套接字:建立监听套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == SOCKET_ERROR) // or == -1
	{
		std::cout << "通信套接字创建失败: " << GetLastError() << std::endl;
		// 版本协议清理
		WSACleanup();
		return -1;
	}
	std::cout << "通信套接字创建成功" << std::endl;

// 确定服务器协议地址簇
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.S_un.S_addr = INADDR_ANY; // 这里可替换成INADDR_ANY。192.168.1.101
	saddr.sin_port = htons(SERVER_PORT);

// 绑定bind:本地IP与分配的端口号port
	int rbin = bind(serverSocket, (sockaddr *)&saddr, sizeof(saddr));
	if(rbin == -1)
	{
		std::cout << "绑定IP和端口失败: " << GetLastError() << std::endl;
		// 版本协议清理 + 关闭通信套接字
		WSACleanup();
		closesocket(serverSocket);
		return -1;
	}
	std::cout << "绑定成功" << std::endl;

// 开始监听
	int rlis = listen(serverSocket, 128); // 设置一次性最多监听128个连接请求
	if(rlis == -1)
	{
		std::cout << "监听失败 : " << GetLastError() << std::endl;
		// 版本协议清理 + 关闭通信套接字
		WSACleanup();
		closesocket(serverSocket);
		return -1;
	}
	std::cout << "服务端正在监听连接，请稍等..." << std::endl;

// 接收连接
	pool.submitTask(conn_sock, serverSocket, &pool);

	getchar();

// 版本协议清理
	WSACleanup();

	return 0;
}

void conn_sock(SOCKET serverSocket, Threadpool* pool)
{
// 接收连接
	while(true)
	{
		std::unique_lock<std::mutex>lock(cs_mutex_);
		cs_cond.wait(lock, []()->bool {return clientSocket.size() < MAX_CONNECT; });

		SOCKADDR_IN caddr;
		int caddrlen = sizeof(caddr);
		SOCKET cs = accept(serverSocket, (sockaddr*)&caddr, &caddrlen);
		if(cs == SOCKET_ERROR)
		{
			std::cout << "服务器崩溃：" << GetLastError << std::endl;
			break;
		}

		clientSocket.emplace_back(cs);
		cs_cond.notify_all();

		char* IP = inet_ntoa(caddr.sin_addr);
		u_short port = ntohs(caddr.sin_port);
		conn_tips(serverSocket, &caddr);
		pool->submitTask(chat_sock, cs, &caddr);
	}

	// 关闭通信套接字
	closesocket(serverSocket);
}

void chat_sock(int socket, SOCKADDR_IN *addr)
{
	char* IP = inet_ntoa(addr->sin_addr);
	u_short port = ntohs(addr->sin_port);

	while(1)
	{
		// 接收消息
		char recv_buf[BUFFER_SIZE];	 // 接收消息存储在buf中，作为参数传入
		char send_buf[BUFFER_SIZE];
		int rlen = recv(socket, recv_buf, BUFFER_SIZE, 0);
		if(rlen == 0)
		{
			for (size_t i = 0; i < clientSocket.size(); i++)
			{	
				sprintf(send_buf, "IP: %s - port: %d 断开连接", IP, port);
				send(clientSocket[i], send_buf, sizeof(send_buf), 0);
			}
			break;
		}
		else if(rlen == SOCKET_ERROR)
		{
			for (size_t i = 0; i < clientSocket.size(); i++)
			{	
				sprintf(send_buf, "IP: %s - port: %d 断开连接", IP, port);
				send(clientSocket[i], send_buf, sizeof(send_buf), 0);
			}
			break;
		}
		else
		{	
			for (size_t i = 0; i < clientSocket.size(); i++)
			{	
				sprintf(send_buf, "IP: %s - port: %d say:\n %s", IP, port, recv_buf);
				send(clientSocket[i], send_buf, sizeof(send_buf), 0);
			}
		}
	}

	for (size_t i = 0; i < clientSocket.size(); i++)
	{
		if(clientSocket[i] == socket)
		{
			clientSocket.erase(clientSocket.begin()+i);
			break;
		}
	}
	cs_cond.notify_all();
	
	closesocket(socket);
}

void conn_tips(SOCKET socket, SOCKADDR_IN* addr)
{
	char *ip = inet_ntoa(addr->sin_addr);
	u_short port = ntohs(addr->sin_port);

	char send_buf[BUFFER_SIZE]; // 发送消息存储在buf中，作为参数传入
	
	// 发送消息
	sprintf(send_buf, "IP: %s - port: %d 连接成功...", ip, port);  
	for (size_t i = 0; i < clientSocket.size(); i++)
	{
		send(clientSocket[i], send_buf, sizeof(send_buf), 0);
	}
}