# include <iostream>
# include <thread>
# include <future>
# include "threadpool_Last.h"

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
void sum3(int a, int b)
{   
    std::cout << "a = " << a << "b = " << b << std::endl;
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

    pool.submitTask(sum3, 1, 2);
    std::cout << "res1: " << res1.get() << std::endl;
    std::cout << "res2: " << res2.get() << std::endl;
    std::cout << "res3: " << res3.get() << std::endl;


    return 0;
}