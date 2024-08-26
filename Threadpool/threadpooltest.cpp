# include <iostream>
# include "threadpool.h"
# include <chrono>
# include <thread>

using uLong = unsigned long long;

class MyTask : public Task
{
    public:
        MyTask(int begin, int end)
            : begin_(begin)
            , end_(end)
        {}

        // 问题1：怎么设计 run 函数返回值可以表示 任何类型-----> Any
        Any run()
        {
            std::cout << "tid: " << std::this_thread::get_id()
                << " begin!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            uLong result = 0;
            for (size_t i = this->begin_; i < this->end_; i++)
            {
                result += i;
            }
            std::cout << "tid: " << std::this_thread::get_id()
                << " end!" << std::endl;
            return result;
        }

    int begin_;
    int end_;
};



int main()
{
    {
        Threadpool pool;
        pool.setMood(PoolMode::MOOD_CACHED);
        pool.start(4);

        Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        Result res3 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res4 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res5 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res6 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        
        uLong sum1 = res1.get().cast_<uLong>();     // get()任务阻塞在这里等待任务结束提供返回值
        uLong sum2 = res2.get().cast_<uLong>();
        uLong sum3 = res3.get().cast_<uLong>();
        uLong sum4 = res4.get().cast_<uLong>();
        uLong sum5 = res5.get().cast_<uLong>();
        uLong sum6 = res6.get().cast_<uLong>();
        std::cout << sum1 << std::endl;
    }
    std::cout << "main over !!" << std::endl;

#if 0
    // 问题 Threadpool析构后，如何回收线程池中的资源
    {
        Threadpool pool;
        // 用户自己设置线性池的工作模型 Fixed/Cache
        pool.setMood(PoolMode::MOOD_CACHED);
        pool.start(4);
        
        // 提交任务
        // 问题2：如何设置 Result 机制
        Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        Result res3 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res4 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res5 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        Result res6 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));

        // 问题3：get()返回了一个Any类型，如何转成一个用户类型
        uLong sum1 = res1.get().cast_<uLong>();
        uLong sum2 = res2.get().cast_<uLong>();
        uLong sum3 = res3.get().cast_<uLong>();
        uLong sum4 = res4.get().cast_<uLong>();
        uLong sum5 = res5.get().cast_<uLong>();
        uLong sum6 = res6.get().cast_<uLong>();

        // result = sum1 + sum2 + sum3;
        // Master - Slave 线程模型
        // Master线程用来分解任务，然后给各个Salve线程分配任务
        // 等待各个Slave线程执行完任务， 返回输出结果
        // Master 线程合并各个任务结果，输出
        std::cout << (sum1 + sum2 + sum3) << std::endl;
    }
#endif
    return 0;
}