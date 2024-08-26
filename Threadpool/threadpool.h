# ifndef THREADPOOL_H
# define THREADPOOL_H
# include <vector>
# include <queue>
# include <memory>
# include <atomic>
# include <mutex>
# include <condition_variable>
# include <functional>
# include <thread>

class Result;
class Any;

// 任务抽象基类
class Task
{
    /*
        任务类型：
        1，不需要返回值的独立任务
        2，需要返回值的独立任务  -- Any + Result
        3，非独立任务           -- 通过信号量Semaphore控制顺序
    */
    public:
        Task();
        ~Task() = default;
        void exec();
        void setResult(Result* res);
        // 用户可以自定义任意任务类型，从 Task 继承，重写 run 方法，实现自定义任务类型
        virtual Any run() = 0;
    private:
        Result* result_;   // 这里注意不能使用智能指针，不然会产生智能指针的循环引用（Result类中有个智能指针）
};

// Any类型：可以接受任意数据的类型
// 模板类的代码声明和实现都只能放在头文件
class Any
{
    public:
        Any() = default;
        ~Any() = default;
        Any(const Any&) = delete;               // 禁止左值引用（成员函数中有独占指针）
        Any& operator=(const Any&) = delete;    // 禁止左值引用（成员函数中有独占指针）
        Any(Any&&) = default;
        Any& operator=(Any&&) = default;

        // 这个构造函数可以使得Any接受任意类型数据
        template<typename T>
        Any(T data) : base_(std::make_unique<Derive<T>>(data))
        {}

        // 这个函数可以使得把Any类型中的数据提取出来
        template<typename T> 
        T cast_()
        {
            // 问题4：如何从base_找到它所指向的Deriver对象，从它里面取出data成员变量
            // 基类指针转成-->派生类指针
            Derive<T> *pd = dynamic_cast<Derive<T>*>(this->base_.get());
            if (pd == nullptr)
            {
                throw "type is unmatch";
            }
            
            return pd->data_;
        }
    private:
        // 基类类型
        class Base
        {
            public:
                virtual ~Base() = default; // ==   virtual ~Base(){};
        };
        // 派生类型
        template<typename T>
        class Derive : public Base
        {
            public:
                Derive(T data) : data_(data)
                {}
                T data_;
        };
    private:
        // 定义一个基类指针
        std::unique_ptr<Base> base_;
};

// 实现一个信号量类
class Semaphore
{
    public:
        Semaphore(int limit = 0);
        ~Semaphore() = default;

        // 获取一个信号量资源
        void wait();
        // 增加一个信号量资源
        void post();
    private:
        std::atomic_bool isExit_;
        int resLimit_;
        std::mutex mtx_;
        std::condition_variable cond_;
};

// 提交任务到线程池，要求线程执行完毕会返回一个值，现在定义这个返回值类型 Result
class Result
{
    public:
        Result(std::shared_ptr<Task> task, bool isValid = true);
        ~Result() = default;
        
        // 问题1：setValue方法，获得任务执行完的返回值
        void setValue(Any any);
        // 问题2：get()方法，用户调用获得task返回值
        Any get();

    private:
        Any any_;           // 存储任务的返回值
        Semaphore Sem_;     // 线程通信信号量
        std::shared_ptr<Task> task_;    // 指向对应获取返回值的对象
        std::atomic_bool isValid_;      // 返回值是否有效(任务是否提交成功)
};


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
        ~Thread();

        // 启动线程
        void start();

        int getId() const;
    private:
        ThreadFunc func_;
        static int generateId_;
        int thread_Id_;     // 保存线程id
};


/*
example:
Threadpool pool;
pool.start(4);

class MyTask : public Task
{
    public:
        void run(){ ...所要运行的代码...}
};
pool.submit(std::make_shared<MyTask>());
*/


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
        Result submitTask(std::shared_ptr<Task> sp);

        // 禁止用户进行拷贝构造
        Threadpool(const Threadpool&) = delete;
        Threadpool& operator=(const Threadpool&) = delete;

    private:
        // 定义线程函数
        void threadFunc(int threadid);

        // 检查pool的运行状态
        bool checkRunningState();

    private:
        // std::vector<std::unique_ptr<Thread>> threads;   // 线程列表
        std::unordered_map<int, std::unique_ptr<Thread>> threads_; // 线程列表
        int initThreadsize_;         // 初始线程数量
        int threadSizeThreshHold_;   // 线程的上限阈值
        std::atomic_uint curThreadSize_;         // 当前线程数量
        std::atomic_uint idleThreadSize_;     // 空闲线程数量
        
        std::queue<std::shared_ptr<Task>> taskQue_;     // 任务队列
        std::atomic_uint taskSize_;     // 任务数量
        int taskQueMaxThreshHold_;      // 任务队列数量上限阈值

        std::mutex taskQueMtx_;         // 保证任务队列的线程安全
        std::condition_variable NotFUll_;    // 表示任务队列不满
        std::condition_variable NotEmpty_;   // 表示任务队列不空
        std::condition_variable exitCond_;   // 等待线程资源全部回收

        PoolMode poolMode_;             // 当前线程池的工作模型
        std::atomic_bool isPoolRunning_;// 当前线程池的启动状态：线性池启动之前，可以进行设置
};

#endif