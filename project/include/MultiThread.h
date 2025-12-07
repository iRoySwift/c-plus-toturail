#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

class ThreadSafeCounter
{
private:
    int count;
    std::mutex mtx;

public:
    ThreadSafeCounter(int count) : count(count) {

                                   };
    void increment(int v)
    {
        std::lock_guard<std::mutex> lock(mtx);
        count += v;
    };
    int getCount() const
    {
        return count;
    };
};

class MultiThreadDemo
{
public:
    void runCounterTest(int threadCount, int incrementsPerThread)
    {
        ThreadSafeCounter safeCounter = {0};
        std::vector<std::thread> threads;
        for (int i = 0; i < threadCount; i++)
        {
            threads.emplace_back(&ThreadSafeCounter::increment, &safeCounter, incrementsPerThread);
            // std::thread t(&ThreadSafeCounter::increment, &safeCounter, incrementsPerThread);
            // t.join();
        }

        for (auto &t : threads)
        {
            t.join();
        }
        int num = safeCounter.getCount();

        std::cout << "counter值为: " << num << std::endl;
    };
    void measurePerformance()
    {
        auto start = std::chrono::high_resolution_clock::now();
        runCounterTest(10, 100);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "执行时间 微秒： " << duration.count() << std::endl;
    };
};

int test_multi_thread()
{
    MultiThreadDemo demo;

    // 测试多线程计数
    demo.runCounterTest(5, 1000);

    // 测量性能
    demo.measurePerformance();

    return 0;
}
