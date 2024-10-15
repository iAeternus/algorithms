#include <iostream>

constexpr long double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628;

// 给定圆的半径r，求圆的直径、周长及面积
void get_circle_info(double r, double &d, double &c, double &s)
{
    d = r * 2;
    c = PI * d;
    s = PI * r * r;
}

int main()
{
    double r;
    std::cin >> r;
    double d, c, s;
    get_circle_info(r, d, c, s);
    std::cout << d << ' ' << c << ' ' << s << std::endl;
    return 0;
}
