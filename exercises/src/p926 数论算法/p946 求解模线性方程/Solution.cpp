/*
求解模线性方程
ax b 模 n 同余
已知 a b n 求 x

eg: 14x 30 模 100 同余 (a = 14 b = 30 n = 100) -> x = 95 & 45
*/
#include <iostream>  
  
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
  
void modular_linear_equation_solver(int a, int b, int n)  
{  
    int x = 0, y = 0;  
    int d = extended_euclid(a, n, x, y);  
    if(b % d != 0) // 当b不能被d整除时，无解  
    {  
        std::cout << "No solutions" << std::endl;
    }  
    else  
    {  
        int x0 = x * (b / d) % n;  
        for (int i = 0; i < d; i++)   
        {  
            std::cout << (x0 + i * (n / d)) % n << std::endl;  
        }
    }  
}  
  
int main()  
{  
    int a, b, n;  
    std::cin >> a >> b >> n;  
    modular_linear_equation_solver(a, b, n);  
    return 0;  
}