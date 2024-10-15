#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

#include "../1.Benchmarking/Timer.h"

template<typename T, typename Compare>
void Merge(std::vector<T>& arr, int left, int mid, int right, Compare comp)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<T> leftArr(n1), rightArr(n2);
    int i, j;
    for (i = 0; i < n1; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        rightArr[j] = arr[mid + j + 1];
    }
    i = j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (comp(leftArr[i], rightArr[j]))
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < n1)
    {
        arr[k++] = leftArr[i++];
    }
    while (j < n2)
    {
        arr[k++] = rightArr[j++];
    }
}

template<typename T, typename Compare>
void Merge_sort(std::vector<T>& arr, int left, int right, Compare comp)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        Merge_sort(arr, left, mid, comp); // 左递归
        Merge_sort(arr, mid + 1, right, comp); // 右递归
        Merge(arr, left, mid, right, comp); // 合并问题解
    }
}

template<typename T, typename Compare>
void Merge_sort(std::vector<T>& arr, Compare comp)
{
    Merge_sort(arr, 0, arr.size() - 1, comp);
}

int main()
{
    int n = 1000;
    srand((unsigned int)time(0));
    std::vector<int> arr(n);
    for(int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 1000;
    }

    Timer::automatic_measurement_of_time([&]() -> void {  
        Merge_sort(arr, [](const int& a, const int& b) -> bool {
            return a > b;  
        });
    }, "merge sort number", 10);

    // for (int i = 0; i < arr.size(); i++)
    // {
    //     std::cout << arr[i] << ' ';
    // }
    // std::cout << '\n';

    std::vector<std::string> names = { "John", "Alice", "Bob", "Charlie" };

    Timer::automatic_measurement_of_time([&]() -> void {
        Merge_sort(names, [](const std::string& a, const std::string& b) -> bool {
            return a < b;
        });
    }, "merge sort string", 10);
    
    // for (const auto& name : names)
    // {
    //     std::cout << name << ' ';
    // }
    // std::cout << '\n';

    return 0;
}