/**
 * std::atomic 原子操作
 */
#include <iostream>
#include <thread>
// #include <mutex> //这个例子不需要mutex了
#include <atomic>

std::atomic_int n = 0;

void count10000()
{
    for (int i = 1; i <= 10000; i++)
    {
        n++;
    }
}

int main()
{
    std::thread th[100];
    for (std::thread &x : th)
        x = std::thread(count10000);
    for (std::thread &x : th)
        x.join();
    std::cout << n << std::endl;
    return 0;
}
