#include <iostream>
#include <thread>

void countNumber(int id, int n)
{
    for(int i = 0; i < n; ++i);
    std::cout << "Thread " << id << " finished!\n";
}

int main()
{
    std::thread threads[10];
    for(int i = 0; i < 10; ++i)
    {
        // thread在传递参数时，是以右值传递的，故不能传递引用
        threads[i] = std::thread(countNumber, i, 1000000); 
    }

    for(int i = 0; i < 10; ++i)
    {
        threads[i].join(); // 10 个线程异步执行，结果混乱
    }
    return 0;
}