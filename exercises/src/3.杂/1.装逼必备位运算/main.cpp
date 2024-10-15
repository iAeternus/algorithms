#include <iostream>
#include <vector>
#include <bitset>

// 将一个数字除以 2
int Divide_by_2(int number)
{
    return number >> 1; // 右移一位
}

// 将一个数字乘 2
int Multiply_by_2(int number)
{
    return number << 1; // 左移一位
}

// 快速求 2 的 n 次幂
int Power_of_2(int n)
{
    return 1 << n;
}

// 判断奇数/偶数
bool isOdd(int number)
{
    return number & 1; // 看二进制最低位是否为 1
}

// 不使用中间变量交换两个元素
void swap(int& a, int& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

// 快速求余数 (模数只能是 2 的幂)
int Remainder(int a, int b)
{
    return a & (b - 1); // b 只能是 2 的幂
}

// 找出只出现一次的数
int Appears_only_once(std::vector<int>& arr)
{
    // a ^ a = 0
    // a ^ 0 = a
    int ret = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        ret ^= arr[i];
    }
    return ret;
}

// 获取某个数的二进制第 k 位
bool get_kth_bit(int number, int k)
{
    return (number & (1 << k)) >> k;
}

// 将二进制的第 k 位设置为 1
void set_kth_bit_to_1(int& number, int k)
{
    number |= (1 << k);
}

int main()
{
    std::cout << "Divide by 2: 1024 / 2 = " << Divide_by_2(1024) << std::endl;
    std::cout << "Multiply by 2: 1024 * 2 = " << Multiply_by_2(1024) << std::endl;
    std::cout << "Power of 2: 2 ^ 10 = " << Power_of_2(10) << std::endl;
    std::cout << "isOdd: 10 -> " << (isOdd(10) ? "odd" : "even") << std::endl;
    std::cout << "isOdd: 11 -> " << (isOdd(11) ? "odd" : "even") << std::endl;

    int a = 1, b = 2;
    swap(a, b);
    std::cout << "swap: 1, 2 -> " << a << ", " << b << std::endl;

    std::cout << "Molding method: 123456789 % 1024 = " << 123456789 % 1024 << std::endl;
    std::cout << "Fast remainder: 123456789 % 1024 = " << Remainder(123456789, 1024) << std::endl;

    std::vector<int> arr = { 20, 30, 20, 10, 10 };
    std::cout << "Find out the number that appears only once in 20, 30, 20, 10, 10 -> "
        << Appears_only_once(arr) << std::endl;

    int number = 16;
    std::cout << "Gets the k-th binary bit of a number: \n number -> " << (std::bitset<8>)number
        << " -> " << "k = 2: " << get_kth_bit(number, 2) << " k = 4: " << get_kth_bit(number, 4) << std::endl;

    std::cout << "Set the k-th bit of the binary to 1: \n number -> " << (std::bitset<8>)number;
    set_kth_bit_to_1(number, 2);
    std::cout << " -> " << "k = 2: " << (std::bitset<8>)number;
    set_kth_bit_to_1(number, 4);
    std::cout << " k = 4: " << (std::bitset<8>)number << std::endl;
    return 0;
}