# include <iostream>
# include <thread>
# include <future>
# include "threadpooh_Last.h"


/*
    1，如何让线程池提交任务更加方便：之前：Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        pool.submitTask(sum1, 1, 2);
        pool.submitTask(sum2, 1, 2, 3);
    
    2, 任务返回值
        c++11 线程库中 packaged_task(本质上时function但是多了一个get_future()) 获得返回值
        使用 future 代替 Result
*/ 

int sum1(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return a + b;
}
int sum2(int a, int b, int c)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return a + b + c;
}

int main()
{
    Threadpool pool;
    // pool.setMood(PoolMode::MOOD_CACHED);
    pool.setTaskQueMaxThreshHold(2);
    pool.start(2);

    std::future<int> res1 = pool.submitTask(sum1, 1, 2);
    std::future<int> res2 = pool.submitTask(sum2, 1, 2, 4);
    std::future<int> res3 = pool.submitTask([](int a)->int {
        int res = 0;
        for (size_t i = 0; i < a; i++)
        {
            res += i * i;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return res;
    }, 4);
    
    std::future<int> res4 = pool.submitTask(sum2, 1, 2, 4);
    std::future<int> res5 = pool.submitTask(sum2, 1, 2, 4);

    std::cout << "res1: " << res1.get() << std::endl;
    std::cout << "res2: " << res2.get() << std::endl;
    std::cout << "res3: " << res3.get() << std::endl;
    std::cout << "res4: " << res4.get() << std::endl;
    std::cout << "res5: " << res5.get() << std::endl;

    return 0;
}