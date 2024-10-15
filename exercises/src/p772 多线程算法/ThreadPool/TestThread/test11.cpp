#include <iostream>
#include <thread>
#include <atomic>

std::atomic_bool ready = false;

// uintmax_t ==> unsigned long long
void sleep(uintmax_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void count()
{
    while (!ready)
    {
        std::this_thread::yield();
    }
    for (int i = 0; i <= 20'0000'0000; i++);
    std::cout << "Thread " << std::this_thread::get_id() << " finished!" << std::endl;
    return;
}

int main()
{
    std::thread th[10];
    for (int i = 0; i < 10; i++)
    {
        th[i] = std::thread(count);
    }
    sleep(5000);
    ready = true;
    std::cout << "Start!" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        th[i].join();
    }
    return 0;
}
