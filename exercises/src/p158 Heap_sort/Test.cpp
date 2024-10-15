#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include <cmath>

#include "Heap.h"

void TestInt(int intLen = 3) // intLen 位数
{
    srand((unsigned int)time(nullptr));
    int size;
    std::cout << "size = ";
    std::cin >> size;
    std::vector<int> arr;
    int upRange = std::pow(10, intLen);
    int lowRange = std::pow(10, intLen - 1);
    for(int i = 0; i < size; i++)
    {
        int num = rand() % (upRange - lowRange) + lowRange;
        arr.push_back(num);
    }
    std::cout << "Before > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    Heap<int> greater;
    greater.HeapSort(arr);

    std::cout << "End > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}

void TestString(int stringLen = 3) // stringLen 位字符串
{
    srand((unsigned int)time(nullptr));
    int size;
    std::cout << "size = ";
    std::cin >> size;
    std::vector<std::string> arr;
    std::string str;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < stringLen; j++) 
        {
            char ch = rand() % 26 + 65;
            str += ch;
        }        
        arr.push_back(str);
        str.clear();
    }
    std::cout << "Before > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    Heap<std::string, less> less;
    less.HeapSort(arr);

    std::cout << "End > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    TestString(3);

    return 0;
}