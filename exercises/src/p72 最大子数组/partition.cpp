#include <iostream>
#include <vector>
#include <tuple>

template<typename T>
std::tuple<int, int, int> Find_max_crossing_subarray(const std::vector<T>& arr, int low, int mid, int high)
{
    int left_sum = std::numeric_limits<T>::min();
    int sum = 0;
    int max_left = low;  // 初始化为 low
    for(int i = mid; i >= low; i--) // mid 左边
    {
        sum += arr[i];
        if(sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = std::numeric_limits<T>::min();
    sum = 0;
    int max_right = high; // 初始化为 high
    for(int j = mid + 1; j <= high; j++) // mid 右边
    {
        sum += arr[j];
        if(sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }
    return std::make_tuple(max_left, max_right, left_sum + right_sum);
}

template<typename T>
std::tuple<int, int, int> Find_maximum_subarray(const std::vector<T>& arr, int low, int high)
{
    if (high == low)
    {
        return std::make_tuple(low, high, arr[low]);
    }
    else
    {
        int mid = low + (high - low) / 2;
        auto [left_low, left_high, left_sum] = Find_maximum_subarray(arr, low, mid);
        auto [right_low, right_high, right_sum] = Find_maximum_subarray(arr, mid + 1, high);
        auto [cross_low, cross_high, cross_sum] = Find_max_crossing_subarray(arr, low, mid, high);
        if (left_sum >= right_sum && left_sum >= cross_sum)
        {
            return std::make_tuple(left_low, left_high, left_sum);
        }
        else if (right_sum >= left_sum && right_sum >= cross_sum)
        {
            return std::make_tuple(right_low, right_high, right_sum);
        }
        else
        {
            return std::make_tuple(cross_low, cross_high, cross_sum);
        }
    }
}

// 时间复杂度 O(nlogn)
template<typename T>
std::tuple<int, int, int> Find_maximum_subarray(std::vector<T>& arr)
{
    return Find_maximum_subarray(arr, 0, arr.size() - 1);
} 

int main()
{
    std::vector<int> arr = {1, -2, 4, 5, -2, 8, 3, -2, 6, 3, 7, -1};
    auto [max_low, max_high, max_sum] = Find_maximum_subarray(arr);
    for(int i = max_low; i <= max_high; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n' << "The maximum value = " << max_sum << std::endl;
    return 0;
}