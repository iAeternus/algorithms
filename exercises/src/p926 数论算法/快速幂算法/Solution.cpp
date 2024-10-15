/*
快速幂算法，快速计算 (a ^ b) % n
eg:
7^560 % 561 = 1
*/
#include <iostream>

using ll = long long;
constexpr ll eps = 561;
#define SOLUTION_2

// 快速幂 求 a 的 b 次方
ll modular_exponentiation(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = res * a % eps;
        }
        // a=a*a
        a = a * a % eps;

        b >>= 1;
    }
    return res;
}

/*
获取整数的二进制表示位数
不断地将输入的整数右移一位，并计数，直到整数变为0
*/
ll countBits(ll b)
{
    ll count = 0;
    while (b != 0)
    {
        b = b >> 1; // 右移一位
        count++;
    }
    return count;
}

// 判断整数 b 的第 i 位二进制表示为 1
bool isBitOne(ll b, ll n)
{
    ll mask = 1 << (n - 1); // 创建掩码，只有第 n 位是 1
    ll result = b & mask;   // 与运算
    return result != 0;      // 如果结果不为 0，那么第 n 位是 1
}

ll modular_exponentiation(ll a, ll b, ll n)
{
    ll c = 0, d = 1;
    int k = countBits(b);
    for (int i = k; i >= 0; --i)
    {
        c *= 2;
        d = (d * d) % n;
        if (isBitOne(b, i))
        {
            ++c;
            d = (d * a) % n;
        }
    }
    return d;
}

int main()
{
#ifdef SOLUTION_1
    ll a, b;
    std::cin >> a >> b;
    std::cout << modular_exponentiation(a, b) << std::endl;
#elif defined(SOLUTION_2)
    ll a, b, n;
    std::cin >> a >> b >> n;
    std::cout << modular_exponentiation(a, b, n) << std::endl;
#endif
    return 0;
}