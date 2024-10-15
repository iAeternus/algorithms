/**
 * @brief 桶排序 期望时间复杂度 O(n)
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <ctime>
#include <cmath>

template <typename T>
void Bucket_Sort(std::vector<T> &arr)
{
    T maxVal = *std::max_element(arr.begin(), arr.end());
    T minVal = *std::min_element(arr.begin(), arr.end());
    int size = static_cast<int>(maxVal - minVal + 1);
    std::vector<std::list<T>> hash(size);

    for (int i = 0; i < arr.size(); i++)
    {
        hash[static_cast<int>(arr[i] - minVal)].push_back(arr[i]);
    }

    int index = 0;
    for (int i = 0; i < hash.size(); i++)
    {
        hash[i].sort();
        for (const auto &it : hash[i])
        {
            arr[index++] = it;
        }
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
    for (int i = 0; i < size; i++)
    {
        int num = rand() % (upRange - lowRange) + lowRange;
        arr.push_back(num);
    }
    std::cout << "Before > \n";
    for (const auto &it : arr)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    Bucket_Sort(arr);

    std::cout << "End > \n";
    for (const auto &it : arr)
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