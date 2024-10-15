#include <iostream>
#include <thread>

template <class T>
void changeValue(T &x, T val)
{
    x = val;
}

int main()
{
    std::thread th[100];
    int nums[100];
    for (int i = 0; i < 100; i++)
    {
        // 传递引用，必须使用
        // std::ref 可以包装按引用传递的值。
        // std::cref 可以包装按const引用传递的值.
        th[i] = std::thread(changeValue<int>, std::ref(nums[i]), i + 1);
    }

    for (int i = 0; i < 100; i++)
    {
        th[i].join();
        std::cout << nums[i] << std::endl;
    }
    return 0;
}
