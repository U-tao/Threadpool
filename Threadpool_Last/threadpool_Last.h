# ifndef THREADPOOL_H
# define THREADPOOL_H
# include <iostream>
# include <queue>
# include <memory>
# include <atomic>
# include <mutex>
# include <condition_variable>
# include <functional>
# include <thread>
# include <future>


// 线程池支持的模型
enum class PoolMode
{
    // Fixed --> Cache 模式的三个问题
    // 1，如何将线性池转为 Cache模型
    // 2，如何根据任务数量和空闲线程数量，判断是否创建新线程
    // 3，如何回收线程
    MOOD_FIXED,     // 固定数量的线程池
    MOOD_CACHED,    //线程数量可动态增长
};

// 线程类型
class Thread
{
    public:
        // 线程函数对象类型
        using ThreadFunc = std::function<void(int)>;

        // 构造函数
        Thread(ThreadFunc func);

        // 析构函数
        ~Thread() = default;

        // 启动线程
        void start();

        int getId() const;

    private:
        ThreadFunc func_;
        static int generateId_;
        int thread_Id_;     // 保存线程id
};


// 线程池类型
class Threadpool
{
    public:
        // 线程池构造
        Threadpool();

        // 线程池析构
        ~Threadpool();

        // 开启线程池
        void start(size_t initThreadSize= std::thread::hardware_concurrency());

        // 设置线程池工作模型
        void setMood(PoolMode mode);

        // 设置task任务队列的上线阈值
        void setTaskQueMaxThreshHold(size_t Threshhold);

        // 设置Thread线程数组的上线阈值(Cache 模式下)
        void setThreadSizeThreshHold(size_t Threshhold);

        // 给线程池提交任务(智能指针)
        // 使用可变参模板编程，让submitTask可以接收任意 任务函数 和 任意数量的参数
        // Result submitTask(std::shared_ptr<Task> sp);
        // submitTask 的返回值类型为 std::future<函数返回值类型>
        //          C++14 提供函数decltype(func(参数)),可以不运行而推导函数(参数)的返回值类型
        // 
        template <typename Func, typename... Args> 
        auto submitTask(Func&& func, Args&&... args) 
            -> std::future<decltype(func(args...))>;


        // 禁止用户进行拷贝构造
        Threadpool(const Threadpool&) = delete;
        Threadpool& operator=(const Threadpool&) = delete;

    private:
        // 定义线程函数
        void threadFunc(int threadid);

        // 检查pool的运行状态
        bool checkRunningState();

    private:
        // std::vector<std::unique_ptr<Thread>> threads;                // 线程列表
        std::unordered_map<int, std::unique_ptr<Thread>> threads_;      // 线程列表
        int initThreadsize_;         // 初始线程数量
        int threadSizeThreshHold_;   // 线程的上限阈值
        std::atomic_uint curThreadSize_;         // 当前线程数量
        std::atomic_uint idleThreadSize_;     // 空闲线程数量
        
        
        // 定义一个 Task代表各种函数（这里void()要进一步修改，让Task可以指代任何返回类型的函数对象）
        using Task = std::function<void()>;
        std::queue<Task> taskQue_;     // 任务队列

        std::atomic_uint taskSize_;     // 任务数量
        int taskQueMaxThreshHold_;      // 任务队列数量上限阈值

        std::mutex taskQueMtx_;         // 保证任务队列的线程安全
        std::condition_variable NotFUll_;    // 表示任务队列不满
        std::condition_variable NotEmpty_;   // 表示任务队列不空
        std::condition_variable exitCond_;   // 等待线程资源全部回收

        PoolMode poolMode_;             // 当前线程池的工作模型
        std::atomic_bool isPoolRunning_;// 当前线程池的启动状态：线性池启动之前，可以进行设置
};

template <typename Func, typename... Args> 
auto Threadpool::submitTask(Func&& func, Args&&... args) 
            -> std::future<decltype(func(args...))>
{
    // 打包任务，放入任务队列
    // 获取func的返回值类型
    using RType = decltype(func(args...));
    // std::packaged_task<int(int, int)>，这里通过bind,将参数绑定到函数func内部，故RType()中可以置空
    // forward 保持对象原有的引用形式(左值引用或右值引用)
    auto task = std::make_shared<std::packaged_task<RType()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    );

    std::future<RType> result = task->get_future();

    // 获取锁
    std::unique_lock<std::mutex> lock(this->taskQueMtx_);

    // 线程通信：这里获得锁后等待，直到任务队列空余或者等待 1s 后仍不空余
    if(!this->NotFUll_.wait_for(lock, std::chrono::seconds(1), 
        [&]()->bool {return this->taskSize_ < this->taskQueMaxThreshHold_; }))
    {
        std::cerr << "Sorry, task quene is full, please try again!" << std::endl;
        // 提交失败，这里定义一个值为 0 的返回值
        auto task = std::make_shared<std::packaged_task<RType()>>(
            []()-> RType {return RType(); }
        );
        (*task)();
        return task->get_future();
    }   

    //  有空余：放入 
    // this->taskQue_.emplace(task);
    // 这里任务队列定义类型为void(), 这里需要特殊处理 void没有返回值，没有参数
    // 接收 task时，要外套一层
    // using Task = std::function<void()>;
    this->taskQue_.emplace([task](){
        (*task)();
        });

    this->taskSize_++;

    //通知（任务队列不为空notempty_通知，让线性池赶紧分配线程执行任务）
    this->NotEmpty_.notify_all();    

    // 需要根据任务数量和空闲线程的数量，判断是否需要创建新的线程
    if (this->poolMode_ == PoolMode::MOOD_CACHED
        && this->taskSize_ > this->idleThreadSize_
        && this->curThreadSize_ < this->threadSizeThreshHold_)
    {
        std::cout << "线程增加... " << std::this_thread::get_id() << " generate" 
            << std::endl;

        std::unique_ptr<Thread> ptr = std::make_unique<Thread>(std::bind(&Threadpool::threadFunc, this, std::placeholders::_1)); // 参数占位符
        int threadId = ptr->getId();
        this->threads_.emplace(threadId, std::move(ptr));
        
        this->threads_[threadId]->start();
        this->curThreadSize_++;
        this->idleThreadSize_++;
        
        std::cout << "当前线性池线程数量: " << this->curThreadSize_ << std::endl;
    }

    // 返回值
    return result;
    // 作用域结束，释放锁
}


#endif