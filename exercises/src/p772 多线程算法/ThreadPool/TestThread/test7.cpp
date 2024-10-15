#include <iostream>
// #include <thread> // 这里我们用async创建线程
#include <future> // std::async std::future

template <class... Args>
decltype(auto) sum(Args &&...args)
{
    // C++17折叠表达式
    // "0 +"避免空参数包错误
    return (0 + ... + args);
}

int main()
{
    // 注：这里不能只写函数名sum，必须带模板参数
    std::future<int> val = std::async(std::launch::async, sum<int, int, int>, 1, 10, 100);
    // future::get() 阻塞等待线程结束并获得返回值
    std::cout << val.get() << std::endl; // 111
    return 0;
}
