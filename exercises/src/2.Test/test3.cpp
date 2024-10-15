#include <iostream>

using namespace std;

class A {
public:
    int a;
    double b;

    A(int a, double b) {
        this->a = a;
        this->b = b;
    }
};

void fun(A** p, A a)
{
    new (*p) A(1, 3.14);
    cout << a.a << a.b << endl;
}

int main()
{
    A a(2, 6.28);
    A *p = &a;
    fun(&p, a);
    cout << (*p).a << (*p).b << endl;
    p = nullptr;
    // delete p;
    return 0;
}