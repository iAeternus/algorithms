/**
 * @brief 随机快速选择算法 时间复杂度 O(n)
 * 
*/
#include <iostream>
#include <vector>

static int RandomNum(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

template<typename T>
int Partition(std::vector<T>& arr, int low, int high)
{
    T pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            std::swap(arr[i + 1], arr[j]);
            i++;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
int Randomized_Partition(std::vector<T>& arr, int low, int high)
{
    int random = RandomNum(low, high);
    std::swap(arr[random], arr[high]);
    return Partition(arr, low, high);
}

template<typename T>
std::pair<int, T> Randomized_Select(std::vector<T>& arr, int low, int high, int i)
{
    if(low == high)
    {
        return std::make_pair(low, arr[low]);
    }
    int pivotIndex = Randomized_Partition(arr, low, high);
    int cnt = pivotIndex - low + 1; // 子数组 [low, pivotIndex) 的元素个数

    if(i == cnt) // 主元正好是结果
    {
        return std::make_pair(pivotIndex, arr[pivotIndex]);
    }
    else if(i < cnt) // 要找的元素落在划分的低区
    {
        return Randomized_Select(arr, low, pivotIndex - 1, i);
    }
    else // 要找的元素落在划分的高区
    {
        return Randomized_Select(arr, pivotIndex + 1, high, i - cnt); // 我们所要找元素在高区中是第 i - cnt 小的元素
    }
}

template<typename T>
std::pair<int, T> Randomized_Select(std::vector<T>& arr, int i, bool is_the_ith_smallest = true) // 第 i 小还是第 i 大
{
    return Randomized_Select(arr, 0, arr.size() - 1, is_the_ith_smallest ? i : arr.size() - i + 1);
}

// 查找下中位数
template<typename T>
std::pair<int, T> Find_Median(std::vector<T>& arr)
{
    return Randomized_Select(arr, arr.size() / 2);
}

int main()
{
    std::vector<int> arr = {2, 5, -1, 9, 25, 0, 12, 4, -7, 12};
    std::cout << "Enter i > ";
    int i;
    std::cin >> i;

    auto[index, result] = Randomized_Select(arr, i, false);

    std::cout << "arr[" << index << "] = " << result << std::endl;

    std::cout << "-----------------------------\n";

    auto[medianIndex, median] = Find_Median(arr);

    std::cout << "median = arr[" << medianIndex << "] = " << median << std::endl;

    return 0;
}