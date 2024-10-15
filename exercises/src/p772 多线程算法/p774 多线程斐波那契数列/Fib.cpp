#include <iostream>
// #include <thread>
#include <future>

#include "E:\Study\undergraduate\Develop\1.program\C++ program\3.algorithm\Introduction to Algorithms\Exercises\src\1.Benchmarking\Timer.h"

// 串行版本
long long fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        long long x = fib(n - 1);
        long long y = fib(n - 2);
        return x + y;
    }
}

// 并行版本
long long p_fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        std::future<long long> future_x = std::async(std::launch::async, p_fib, n - 1);
        long long y = p_fib(n - 2);

        // 获取异步执行任务的结果
        long long x = future_x.get();

        return x + y;
    }
}

int main()
{
    int n = 20;
    for (int i = 0; i < n; ++i)
    {
        long long result;
        {
            Timer timer("p_fib");
            result = p_fib(i);
        }
        // std::cout << result << std::endl;
    }

    for (int i = 0; i < n; ++i)
    {
        long long result;
        {
            Timer timer("fib");
            result = fib(i);
        }
        // std::cout << result << std::endl;
    }
    return 0;
}