# C++ VScode项目: 线程池项目
    1, Threadpool: 文件夹中是从零开始,使用c11之前的c++提供的功能一步步进行编写
    2, Threadpool_Last: 文件夹中是通过c11之后,包含c14的提供的新特性,进行编写
    3，Threadpool_Socket: Socket网络编程文件。Windows下，通过线性池实现多人通信的Socket项目。
        *文件 3 为发布程序，通过动态库和cmake生成程序*

## 项目介绍:

## 项目名称:基于可变参模板实现的线程池
    git地址 : git@github.com:U-tao/Threadpool.git
    平台工具 : VSCode, cmake, ubuntu编译so库, gdb调试分析定位死锁问题
## 项目应用方向
    高并发网络服务器
    master-slave线程模型
    耗时任务处理
## 项目描述
    1.	使用Socket套接字技术，实现跨系统的计算机连接与通信。
    2.	采用C++中的thread库函数，解决了聊天窗口中输入和输出消息无法异步操作的问题，实现了同一窗口下多消息的发送和接收。
    3.	运用线程通信和互斥机制，构建高效的线程池，优化了线程管理，减少了用户进出聊天室时出现的bug，增强了代码的健壮性。
    4.	设计了Fixed和Cached两种线程池模型，支持固定线程数和动态线程数切换，有效应对高并发情况下的系统资源不足。
    5.	使用C++11新特性（如future关键字），简化代码结构，减少了约30%的代码量。
    6.	基于ROLL机制设计了线程资源的释放策略，成功解决程序死锁问题，优化了资源回收机制。
    7.	构建了基于可变参模板和引用折叠技术的任务传递接口，支持任意任务函数及参数，提高了代码的可读性和扩展性。
    8.	利用GitHub进行持续集成和部署（CI/CD），实现了自动化构建与部署，提高了开发效率。
    9.	使用CMake配置和部署了我的项目，优化了构建流程，提高了代码的可维护性和可移植性。

## 项目问题:
    1、在ThreadPool的资源回收，等待线程池所有线程退出时，发生死锁问题，导致进程无法退出
    2、在windows平台下运行良好的线程池，在linux平台下运行发生死锁问题，平台运行结果有差异化

## 分析定位问题:
    主要通过gdb atach到正在运行的进程，通过info threads，thread tid，bt等命令查看各个线程的调用堆栈信息，结合项目代码，定位到发生死锁的代码片段，分析死锁问题发生的原因，以及最终的解决方案。
