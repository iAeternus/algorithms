/**
 * @brief 快速排序 时间复杂度 O(nlogn)
 * @brief 稳定性：不稳定
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <cmath>

template<typename ValueType, typename Compare>
int Partition(std::vector<ValueType>& arr, int low, int high, Compare compare)
{
    ValueType pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) 
    {
        if(compare(arr[j], pivot))
        {
            std::swap(arr[i + 1], arr[j]);
            i++;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 随机产生［low, high］的随机数
static int Random(const int low, const int high)
{
    return rand() % (high - low + 1) + low;
}

// 随机选取主元，防止频繁出现最差情况使时间复杂度变为 O(n^2)
template<typename ValueType, typename Compare>
int Randomized_Partition(std::vector<ValueType>& arr, int low, int high, Compare compare)
{
    int random = Random(low, high);
    std::swap(arr[random], arr[high]); // 把一个随机索引指向的元素与主元交换
    return Partition(arr, low, high, compare);
}

template<typename ValueType, typename Compare>
void Quick_Sort(std::vector<ValueType>& arr, int low, int high, Compare compare)
{
    if(low < high)
    {
        int pivot = Randomized_Partition(arr, low, high, compare);
        Quick_Sort(arr, low, pivot - 1, compare);
        Quick_Sort(arr, pivot + 1, high, compare);
    }
}

template<typename ValueType, typename Compare>
void Quick_Sort(std::vector<ValueType>& arr, Compare compare)
{
    Quick_Sort(arr, 0, arr.size() - 1, compare);
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

    Quick_Sort(arr, [](const int& a, const int& b)->bool {
        return a < b;
    });

    std::cout << "End > \n";
    for(const auto& it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}

void TestString(int stringLen = 3)
{
    srand((unsigned int)time(nullptr));
    int size;
    std::cout << "size = ";
    std::cin >> size;
    std::vector<std::string> arr;
    std::string str;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < stringLen; j++) // stringLen 位字符串
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
    Quick_Sort(arr, [](const std::string& a, const std::string& b)->bool {
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
    TestInt(3);

    return 0;
}