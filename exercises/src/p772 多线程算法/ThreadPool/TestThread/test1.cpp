#include <iostream>
#include <thread>

void doSomething()
{
    std::cout << "Hello thread b!\n";
}

int main()
{
    std::thread a([]() {
        std::cout << "Hello thread a!\n";
    }); // 创建线程，可传 lambda

    std::thread b(doSomething); // 创建线程，可传函数指针

    a.join(); // 等待线程结束并清理资源（会阻塞）
    b.join(); // 两次执行的顺序是不一定的

    return 0;
}