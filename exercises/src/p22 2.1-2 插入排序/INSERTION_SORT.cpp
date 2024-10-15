/**
 * @brief 插入排序 时间复杂度 O(n^2)
 * @brief 稳定性：稳定
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

template<typename T, typename Compare>
void insertion_sort(std::vector<T>& arr, Compare comp)
{
    for(int i = 1; i < arr.size(); i++)
    {
        T key = arr[i];
        int j = i - 1;
        while(j >= 0 && comp(key, arr[j]))
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

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
    insertion_sort(arr, [](const int& a, const int& b) {
        return a < b;
    });
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
    insertion_sort(arr, [](const std::string& a, const std::string& b)->bool {
        return a > b;
    });
    std::cout << "End > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    TestInt(4);
    std::cout << "over\n";

    return 0;
}