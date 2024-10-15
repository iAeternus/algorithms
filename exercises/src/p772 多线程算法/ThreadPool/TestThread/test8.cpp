#include <iostream>
#include <future>

void count_big_number()
{
    // C++14标准中，可以在数字中间加上单
    // 引号 ' 来分隔数字，使其可读性更强
    for (int i = 0; i <= 10'0000'0000; i++);
}
int main()
{
    std::future<void> fut = std::async(std::launch::async, count_big_number);
    std::cout << "Please wait" << std::flush;
    // 每次等待1秒
    while (fut.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
    {
        std::cout << '.' << std::flush;
    }

    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;

    return 0;
}
