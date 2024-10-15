/**
 * C++11中的 std::atomic和 std::mutex
 * std::mutex 是 C++11 中最基本的互斥量，一个线程将mutex锁住时，其它的线程就不能操作mutex，直到这个线程将mutex解锁
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>

int n = 0;
std::mutex mtx;

void count10000()
{
    for (int i = 1; i <= 10000; i++)
    {
        mtx.lock();
        n++;
        mtx.unlock();
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
