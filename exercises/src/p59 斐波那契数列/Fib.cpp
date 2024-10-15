#include <iostream>
#include <cmath>

// 非常快的斐波纳契数列通项算法，由于 double 的限制只能算到第 1475 项
double Fib(int i)
{
    double root_of_5 = sqrt(5);
    return floor(pow((1 + root_of_5) / 2, i) / root_of_5 + 0.5);
}

int main()
{
    for(int i = 0; i <= 1474; i++)
    {
        std::cout << Fib(i) << std::endl;
    }
    return 0;
}