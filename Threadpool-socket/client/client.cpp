#include <iostream>
#include <thread>

// windows socket头文件
// 配置文件 tasks.json -> args中加入 "-lwsock32"
#include <winsock2.h>
#include <windows.h>
#pragma commet(lib, "ws2_32.lib")

#define SERVER_IP "192.168.1.101"  
#define SERVER_PORT 8888  
#define BUFFER_SIZE 1024  

SOCKET clientSocket;

void chat_sock(int socket);

int main()
{
	// 初始化套接字库
	// 确定网络协议版本。
	WSADATA wsadata;
	WORD w_req = MAKEWORD(2, 2); // 版本号
	int err = WSAStartup(w_req, &wsadata);
	if(err != 0)
	{
		std::cout << "套接字初始化失败！！！" << std::endl;
	}
	else
	{
		std::cout << "套接字初始化成功" << std::endl;
	}

	// 检测版本号
	if(LOBYTE(wsadata.wVersion) != 2 ||
	   HIBYTE(wsadata.wHighVersion) != 2)
	   {
			std::cout << "套接字库版本不符！！" << GetLastError() << std::endl;
	   		return -1;
	   }
	else
	{
		std::cout << "套接字库版本正确" << std::endl;
	}

// 套接字:建立通信套接字
	// SOCKET WSAAPI socket(int af,int type,int protocol);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == SOCKET_ERROR) // or == -1
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
	saddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); // 这里可替换成INADDR_ANY。
	saddr.sin_port = htons(SERVER_PORT);

// 连接服务器
    int resc = connect(clientSocket, (sockaddr*)&saddr, sizeof(saddr));
    if(resc == -1)
    {
		std::cout << "连接失败: " << GetLastError() << std::endl;
		// 版本协议清理 + 关闭通信套接字
		WSACleanup();
		closesocket(clientSocket);
		return -1;
    }
    std::cout << "连接成功" << std::endl;

    // 通信
    chat_sock(clientSocket);

	// 关闭socket  
	closesocket(clientSocket);
	// 清理Winsock  
	WSACleanup();
    return 0;
}

void chat_sock(int socket)
{
	char recv_buf[1024];	 // 接收消息存储在buf中，作为参数传入
	char send_buf[1024]; // 发送消息存储在buf中，作为参数传入

	std::thread read_t = std::thread([&](){
		while(1)
		{
			// 接收消息
			// int WSAAPI recv(SOCKET s,char *buf,int len,int flags);
			std::cout << "client :";
			memset(recv_buf, '\0' , sizeof(recv_buf));
			int rlen = recv(socket, recv_buf, BUFFER_SIZE, 0);
			if(rlen == 0)
			{
				std::cout << "client connect close ..." << std::endl;
				break;
			}
			else if(rlen == SOCKET_ERROR)
			{
				std::cout << "client message recv failed: " << WSAGetLastError() << std::endl;
				break;
			}
			else
			{	
				std::cout << recv_buf << std::endl;
			}
		}
	});

	std::thread send_t = std::thread([&](){
		while(1)
		{
			// 发送消息
			// int WSAAPI send(SOCKET s,const char *buf,int len,int flags);
			// std::cout << "Server say :";
			memset(send_buf, '\0' , sizeof(send_buf));
			std::cin >> send_buf;
			int slen = send(socket, send_buf, sizeof(send_buf), 0);
			if(slen == SOCKET_ERROR)
			{
				std::cout << "server message send failed: " << WSAGetLastError() << std::endl;
			}
		}
	});

	read_t.join();
	send_t.join();

	closesocket(socket);
}