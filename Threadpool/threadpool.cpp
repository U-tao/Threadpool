# include "threadpool.h"
# include <thread>
# include <iostream>

// 任务队列的上限
const int TASK_MAX_THRESHHLOD = INT32_MAX;
const int THREAD_MAZ_THRESHHLOD = 100;
const int THREAD_MAX_IDLE_TIME = 60; // 单位：秒
// 构造函数：线性池
Threadpool::Threadpool()
    :initThreadsize_(0)     // 初始化线程数量
    ,curThreadSize_(0)      // 当前线程数量
    ,idleThreadSize_(0)     // 空闲线程数量
    ,taskSize_(0)           // 初始化任务数量
    ,taskQueMaxThreshHold_(TASK_MAX_THRESHHLOD) // 任务队列的最大阈值
    ,poolMode_(PoolMode::MOOD_FIXED)            // 线性池的模型（Fixed, Cache)
    ,isPoolRunning_(false)  // 线性池运行状态
    ,threadSizeThreshHold_(THREAD_MAZ_THRESHHLOD)
{}

// 析构函数：线程池
Threadpool::~Threadpool() 
{
    this->isPoolRunning_ = false;
    
    // 等待线程池所有线程返回（结束） 线程两种状态：阻塞/正在运行
    std::unique_lock<std::mutex>lock(this->taskQueMtx_);
    this->NotEmpty_.notify_all();
    this->exitCond_.wait(lock, [&]()->bool {return this->threads_.size() == 0;});
}

// 启动：线程池
void Threadpool::start(size_t initThreadSize)
{
    if (this->poolMode_ == PoolMode::MOOD_FIXED)
    {
        std::cout << "当前线程池模型为：Mood_FIXED" << std::endl;
    }
    else if (this->poolMode_ == PoolMode::MOOD_CACHED)
    {
        std::cout << "当前线程池模型为：Mood_Cache" << std::endl;
    }
    else
    {
        throw "Threadpool poolMode set wrong!!!";
    }

    // 记录初始线程个数
    this->isPoolRunning_ = true;
    this->initThreadsize_ = initThreadSize;
    this->curThreadSize_ = initThreadSize;

    // 创建线程对象
    for (size_t i = 0; i < this->initThreadsize_; i++)
    {
        // 创建线程对象时，把线程函数(treadFunc)给到 thread 线程对象
        std::unique_ptr<Thread> ptr = std::make_unique<Thread>(std::bind(&Threadpool::threadFunc, this, std::placeholders::_1)); // 参数占位符
        // this->threads.emplace_back(std::move(ptr));
        this->threads_.emplace(ptr->getId(), std::move(ptr));
    }

    // 启动所有线程
    for (size_t i = 0; i < this->initThreadsize_; i++)
    {
        this->threads_[i]->start();     // map重载了[],[]里面的值就是key值
        this->idleThreadSize_++;
    }
}

// 设置线程池工作模型
void Threadpool::setMood(PoolMode mode)
{
    if(this->checkRunningState())
        return;
    this->poolMode_ = mode;
}

// 设置task任务队列的上线阈值
void Threadpool::setTaskQueMaxThreshHold(size_t Threshhold)
{
    if(this->checkRunningState())
        return;
    this->taskQueMaxThreshHold_ = Threshhold;
}

// 设置Thread线程数组的上线阈值(Cache 模式下)
void Threadpool::setThreadSizeThreshHold(size_t Threshhold)
{
    if (this->checkRunningState())
    {
        return;
    }
    if (this->poolMode_ == PoolMode::MOOD_CACHED)
    {
        this->threadSizeThreshHold_ = Threshhold;    
    }
}

// 给线程池提交任务(智能指针)--用户调用此接口，传入任务对象（生产任务）
Result Threadpool::submitTask(std::shared_ptr<Task> sp)
{   
    // 获取锁
    std::unique_lock<std::mutex> lock(this->taskQueMtx_);

    // 线程通信：这里获得锁后等待，直到任务队列空余或者等待1s后仍不空余
    if(!this->NotFUll_.wait_for(lock, std::chrono::seconds(1), 
        [&]()->bool {return this->taskSize_ < this->taskQueMaxThreshHold_; }))
    {
        std::cerr << "Sorry, task quene is full, please wait a monment!" << std::endl;
        return Result(sp, false);
    }   

    //  有空余：放入->
    this->taskQue_.emplace(sp);
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
    return Result(sp, true);

    // 作用域结束，释放锁
}

// 线程函数：线程启动时执行的函数
void Threadpool::threadFunc(int threadid)
{
    // 线程开始启动的时间
    auto last = std::chrono::high_resolution_clock().now();

    // 让线程一直寻找任务，结束一个任务后依旧如此
    // while(this->isPoolRunning_) 
    for(;;)
    {   
        // 锁加了作用域，里面取出的task要在作用域外定义
        std::shared_ptr<Task> task;
        {
            // 获取锁
            std::unique_lock<std::mutex> lock(this->taskQueMtx_);

            std::cout << "tid: " << std::this_thread::get_id() 
                << "尝试获取任务..." << std::endl;

            // 线程通信:等待,直到任务队列不为空
            // 每一秒钟返回一次，区分：超时返回/有任务返回
            // 如果队列不为空，不需要进入循环，直接取任务执行。反之进入循环开始等待
            while(this->taskQue_.size() == 0)
            {
                // 线程池结束，回收线性池
                if(!this->isPoolRunning_)
                {
                    // 开始回收线程
                    std::cout << "线程销毁... " << std::this_thread::get_id() << " exit" 
                        << std::endl;
                    this->threads_.erase(threadid);
                    this->exitCond_.notify_all();
                    return;     // 线程函数结束，线程回收
                }

                if(this->poolMode_ == PoolMode::MOOD_CACHED)    // 如果线程池模型为：MOOD_CACHED
                {
                    // 条件变量超时返回
                    if(std::cv_status::timeout == 
                        this->NotEmpty_.wait_for(lock, std::chrono::seconds(1)))
                    {
                        auto now = std::chrono::high_resolution_clock().now();
                        auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - last);
                        if (dur.count() >= THREAD_MAX_IDLE_TIME
                                && this->curThreadSize_ > this->initThreadsize_)
                        {
                            // 开始回收线程
                            std::cout << "线程销毁... " << std::this_thread::get_id() << std::endl;
                            this->threads_.erase(threadid);
                            this->curThreadSize_--;
                            this->idleThreadSize_--;
                            return;
                        }
                    }
                }
                else if (this->poolMode_ == PoolMode::MOOD_FIXED)
                {
                    this->NotEmpty_.wait(lock);
                }
                else
                {
                    throw "Threadpool poolMode set wrong!!!";
                } 
            }
            
            this->idleThreadSize_--;
            std::cout << "tid: " << std::this_thread::get_id() << "获取任务成功！！！" << std::endl;

            // 从任务队列中取出任务运行，.front, .pop, tasksize--,run();
            task = std::move(this->taskQue_.front()); // std::move 独占指针转移所有权
            this->taskQue_.pop();
            this->taskSize_--;

            // 线程通信:如果依然有剩余任务，通知其他线程可以继续执行--> 消耗任务
            if(this->taskSize_ > 0)
            {
                this->NotEmpty_.notify_all();
            }

            // 线程通信:通知提交着可以继续执行--> 生产任务
            this->NotFUll_.notify_all();

            // task 任务运行前，就要把锁释放,所以加一个作用域
        }

        // 任务运行
        if (task != nullptr)
        {
            task->exec();
        }
        this->idleThreadSize_++;
        // 更新线程执行完任务的时间
        last = std::chrono::high_resolution_clock().now();
    }

}

// 返回当前线性池的运行状态
bool Threadpool::checkRunningState()
{
    return this->isPoolRunning_;
}

//=================== 线程方法实现 =================== 
int Thread::generateId_ = 0;

// 构造函数：线程
Thread::Thread(ThreadFunc func)
    : func_(func)
    , thread_Id_(generateId_++)
{}

// 析构函数：线程
Thread::~Thread()
{}

// 启动线程
void Thread::start()
{
    // 创建一个线程并执行一个线程函数
    std::thread t(this->func_, this->thread_Id_);     // C++来说 线程对象t 和线程函数func_
    t.detach();         // 设置分离线程--线程对象出了函数体，自动释放，但是不影响func_线程函数继续执行（线程保持等待状态）

}

int Thread::getId() const
{
    return this->thread_Id_;
}


//=================== Task 可以指向任意类型的类实现 =================== 
Task::Task()
    : result_(nullptr)
{}

void Task::exec()
{
    if(this->result_ != nullptr)
    {   
        this->result_->setValue(this->run());
        std::cout << "任务运行结束..." << std::endl;
    } 
}

void Task::setResult(Result* res)
{
    this->result_ = res;
}
//=================== Any 可以指向任意类型的类实现 =================== 
// Any属于模板类，实现和生命只能在头文件书写

//=================== Semaphore 信号量类实现 =================== 
Semaphore::Semaphore(int limit)
    :resLimit_(limit)
    ,isExit_(false)
{}

void Semaphore::post()
{   
    if(this->isExit_)
        return;
    std::unique_lock<std::mutex> lock(this->mtx_);
    this->resLimit_++;
    this->cond_.notify_all();
}

void Semaphore::wait()
{
    if(this->isExit_)
        return;
    std::unique_lock<std::mutex> lock(this->mtx_);
    this->cond_.wait(lock, [&]()->bool {return this->resLimit_ > 0; });
    this->resLimit_--;
}

//=================== Result 类实现 =================== 
// 析构函数
Result::Result(std::shared_ptr<Task> task, bool isValid)
    : task_(task)
    , isValid_(isValid)
{
    this->task_->setResult(this);
}

Any Result::get()
{
    if(!this->isValid_)
    {
        return "";
    }
    this->Sem_.wait();  // 任务如果没有执行完成，此处阻塞
    return std::move(this->any_);
}

void Result::setValue(Any any)
{   
    this->any_= std::move(any);
    this->Sem_.post();  // 已经获取了任务返回值，增加信号量资源
}