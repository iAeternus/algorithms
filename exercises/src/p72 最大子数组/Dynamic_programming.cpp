#include <iostream>
#include <vector>
#include <tuple>

// 时间复杂度 O(n)
template<typename T>
std::tuple<int, int, int> Find_maximum_subarray(const std::vector<T>& arr)
{
    // 初始化备忘录和追踪数组
    std::vector<int> D(arr.size() + 1), Rec(arr.size() + 1);
    D[arr.size()] = arr[arr.size() - 1];
    Rec[arr.size()] = arr.size() - 1;

    // 动态规划
    for(int i = arr.size() - 1; i >= 0; i--)
    {
        if(D[i + 1] > 0)
        {
            D[i] = arr[i] + D[i + 1];
            Rec[i] = Rec[i + 1];
        }
        else
        {
            D[i] = arr[i];
            Rec[i] = i;
        }
    }

    // 最优方案追踪
    int max_low = 0, max_high = 0, max_sum = D[0];
    for(int i = 0; i < D.size(); i++)
    {
        if(D[i] > max_sum)
        {
            max_sum = D[i];
            max_low = i;
            max_high = Rec[i];
        }
    }
    return std::make_tuple(max_low, max_high, max_sum);
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