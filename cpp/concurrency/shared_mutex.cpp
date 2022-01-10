/*
 * 读写所使用示例
 */
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <shared_mutex>
#include <thread>

std::mutex mtx;

class ThreadSafeCounter
{
private:
    mutable std::shared_mutex mutex_;  // 声明一个读写锁
    unsigned int              value_ = 0;

public:
    ThreadSafeCounter(){};
    ~ThreadSafeCounter(){};

    unsigned int get() const
    {
        // 以读模式加锁，可以多个线程占有只读模式的读写锁
        std::shared_lock<std::shared_mutex> lck(mutex_);
        return value_;
    }

    unsigned int increment()
    {
        // 以写模式加锁，只能有线程占有只读模式的读写锁
        std::unique_lock<std::shared_mutex> lck(mutex_);
        value_++;
        return value_;
    }

    void reset()
    {
        std::unique_lock<std::shared_mutex> lck(mutex_);
        value_ = 0;
    }
};

ThreadSafeCounter counter;

void reader(int id)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> ulck(mtx);
        std::cout << "read #" << id << " get value " << counter.get() << "\n";
    }
}

void writer(int id)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> ulck(mtx);
        std::cout << "write #" << id << " write value " << counter.increment() << "\n";
    }
}

int main(void)
{
    std::thread rth[10];
    std::thread wth[10];
    for(int i = 0; i < 10; i++)
    {
        rth[i] = std::thread(reader, i + 1);
    }

    for(int i = 0; i < 10; i++)
    {
        wth[i] = std::thread(writer, i + 1);
    }

    for(int i = 0; i < 10; i++)
    {
        rth[i].join();
    }
    for(int i = 0; i < 10; i++)
    {
        wth[i].join();
    }

    return 0;
}

