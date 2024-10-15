#include <iostream>

// 欧几里得算法 时间复杂度 O(lgb)
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// 最小公倍数
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

/**
 * 欧几里得算法的扩展形式 时间复杂度 O(lgb)
 * 
 * 定理 31.2  如果任意整数 a 和 b 不都为 0，
 * 则 gcd(a, b) 是 a 与 b 的线性组合集 {ax + by: x, y 输入 Z} 中的最小正元素
*/
int extended_euclid(int a, int b, int& x, int& y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else
    { 
        int x1 = x, y1 = y;
        int d = extended_euclid(b, a % b, x1, y1);
        
        x = y1;
        y = x1 - a / b * y1;
        return d;
    }
}

void print_gcd(int a, int b, int d, int x, int y)
{
    std::cout << "gcd(" << a << ", " << b << ") = " << d;
    std::cout << " = " << a << " * ";
    if(x < 0)
    {
        std::cout << '(' << x << ')';
    }
    else
    {
        std::cout << x;
    }
    std::cout << " + " << b << " * ";
    if(y < 0)
    {
        std::cout << '(' << y << ')' << std::endl;
    }
    else
    {
        std::cout << y << std::endl;
    }
}

int main()
{
    int a = 99;
    int b = 78;
    std::cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;
    std::cout << "lcm(" << a << ", " << b << ") = " << lcm(a, b) << std::endl;
    std::cout << "===============================================================\n";
    int x, y;
    int d = extended_euclid(a, b, x, y); // 获取 最大公约数 和 x, y
    print_gcd(a, b, d, x, y);

    return 0;
}