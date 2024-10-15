#include <iostream>
#include <thread>
#include <future> // std::promise std::future

template <class... Args>
decltype(auto) sum(Args &&...args)
{
    return (0 + ... + args);
}

template <class... Args>
void sum_thread(std::promise<long long> &val, Args &&...args)
{
    val.set_value(sum(args...));
}

int main()
{
    std::promise<long long> sum_value;
    std::thread get_sum(sum_thread<int, int, int>, ref(sum_value), 1, 10, 100);
    std::cout << sum_value.get_future().get() << std::endl;
    get_sum.join();
    return 0;
}
