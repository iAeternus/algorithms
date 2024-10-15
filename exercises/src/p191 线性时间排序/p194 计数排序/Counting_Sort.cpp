#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>

/**
 * @brief 计数排序 时间复杂度 O(n)
 * @brief 稳定性：稳定
 * @brief 缺点：排序对象必须是 0 ~ k 之间的整数
 */
template <typename T>
class Counting_Sorter
{
private:
    static_assert(std::is_integral<T>::value, "T must be an integral type"); // 限制模板类型为整数

public:
    static void Sort(std::vector<T> &arr)
    {
        if (arr.empty())
        {
            throw std::invalid_argument("Array is empty");
        }

        // 查找最大值与最小值
        T maxVal = *std::max_element(arr.begin(), arr.end());
        T minVal = *std::min_element(arr.begin(), arr.end());

        // 计算计数数组的大小
        size_t countSize = static_cast<size_t>(maxVal - minVal + 1);

        // 初始化计数数组为 0
        std::vector<size_t> count(countSize, 0);

        // 统计每个元素的个数
        for (const T &element : arr)
        {
            ++count[static_cast<size_t>(element - minVal)];
        }

        // 进行累加操作，确定对每个 i，有多少输入元素是小于等于 i 的
        for (size_t i = 1; i < countSize; ++i)
        {
            count[i] += count[i - 1];
        }

        // 创建结果数组
        std::vector<T> result(arr.size());

        // 从后向前填充结果数组
        for (int j = static_cast<int>(arr.size()) - 1; j >= 0; --j)
        {
            result[--count[static_cast<size_t>(arr[j] - minVal)]] = arr[j]; // 将 arr[j] 放入正确的位置，计数减一
        }

        arr = result;
    }
};

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

    Counting_Sorter<int>::Sort(arr);

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
    std::cout << "over\n";
    return 0;
}