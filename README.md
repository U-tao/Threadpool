# C++ VScode项目: 线程池项目
    1, Threadpool: 文件夹中是从零开始,使用c11之前的c++提供的功能一步步进行编写
    2, Threadpool_Last: 文件夹中是通过c11之后,包含c14,和c17的提供的新特性,进行编写
    3，Socket: Socket网络编程文件。Windows下，通过线性池实现多人通信的Socket项目。

## 项目介绍:

## 项目名称:基于可变参模板实现的线程池
    git地址 : git@github.com:U-tao/Threadpool.git
    平台工具 : VSCode ubuntu编译so库, gdb调试分析定位死锁问题
## 项目应用方向
    高并发网络服务器
    master-slave线程模型
    耗时任务处理
## 项目描述
    1、基于可变参模板编程和引用折叠原理，实现线程池submitTask接口，支持任意任务函数和任意参数的传递
    2、使用future类型定制submitTask提交任务的返回值
    3、使用map和queue容器管理线程对象和任务
    4、基于条件变量condition_variable和互斥锁mutex实现任务提交线程和任务执行线程间的通信机制
    5、支持fixed和cached模式的线程池定制
## 项目问题:
    1、在ThreadPool的资源回收，等待线程池所有线程退出时，发生死锁问题，导致进程无法退出
    2、在windows平台下运行良好的线程池，在linux平台下运行发生死锁问题，平台运行结果有差异化

## 分析定位问题:
    主要通过gdb atach到正在运行的进程，通过info threads，thread tid，bt等命令查看各个线程的调用堆栈信息，结合项目代码，定位到发生死锁的代码片段，分析死锁问题发生的原因，以及最终的解决方案。
