#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>

template <typename T>
class Radix_Sorter
{
private:
    // 限制模板类型为整数
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

public:
    /*
     * 计数排序
     *
     * 参数说明：
     *     arr -- 数组
     *     exp -- 指数。对数组a按照该指数进行排序。
     *
     * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
     *    (01) 当exp=1表示按照"个位"对数组a进行排序
     *    (02) 当exp=10表示按照"十位"对数组a进行排序
     *    (03) 当exp=100表示按照"百位"对数组a进行排序
     *    ...
     */
    static void count_sort(std::vector<T> &arr, int exp)
    {
        // 存储"被排序数据"的临时数组
        std::vector<T> output(arr.size());
        std::vector<T> buckets(10, 0);

        // 将数据出现的次数存储在buckets[]中
        for (int i = 0; i < arr.size(); i++)
            buckets[(arr[i] / exp) % 10]++;

        // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
        for (int i = 1; i < 10; i++)
            buckets[i] += buckets[i - 1];

        // 将数据存储到临时数组output[]中
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            output[buckets[(arr[i] / exp) % 10] - 1] = arr[i];
            buckets[(arr[i] / exp) % 10]--;
        }

        // 将排序好的数据赋值给arr
        arr = output;
    }

    /*
     * 基数排序
     *
     * 参数说明：
     *     arr -- 数组
     */
    static void Sort(std::vector<T> &arr)
    {
        if (arr.empty())
        {
            throw std::invalid_argument("Array is empty");
        }
        // 指数。当对数组按各位进行排序时，exp=1；按十位进行排序时，exp=10；...
        int exp;
        // 数组a中的最大值
        int max = *std::max_element(arr.begin(), arr.end());

        // 从个位开始，对数组a按"指数"进行排序
        for (exp = 1; max / exp > 0; exp *= 10)
        {
            count_sort(arr, exp);
        }
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

    Radix_Sorter<int>::Sort(arr);

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