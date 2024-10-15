/**
 * @brief 钢条切割问题
 * @brief 输入： 钢条长度 n
 *				价格表 pi (1 <= l <= n)：表示长度为 l 的钢条价格
 *		  输出：求解一组切割方案 T = <c1, c2,..., cm>，在每根钢条的长度之和 == n 的前提下，令价格最大
 * @author Ricky
 * @date 2023/7/31
 * @version 1.0
*/
#include <iostream>
#include <vector>

/**
 * @brief 优化钢条切割问题的动态规划算法
 * @param p 长度为 i 的钢条的价格表
 * @param n 钢条长度
 * @return 返回备忘录数组和追踪数组
 */
std::pair<std::vector<int>, std::vector<int>> Cut_Rod (std::vector<int>& p, int n)
{
    std::vector<int> dist (n + 1); // 备忘录数组
    std::vector<int> rec (n + 1); // 追踪数组
    dist[0] = 0;

    for (int j = 1; j <= n; j++)
    {
        int q = std::numeric_limits<int>::min ();
        rec[j] = j;
        for (int i = 1; i <= j; i++)
        {
            if (i <= p.size ())
            {
                if (q < p[i - 1] + dist[j - i])
                {
                    q = p[i - 1] + dist[j - i];
                    rec[j] = i;
                }
            }
            else // 超出价格表范围的情况取价格为0
            {
                if (q < dist[j - i])
                {
                    q = dist[j - i];
                    rec[j] = i;
                }
            }
        }
        dist[j] = q;
    }

    return std::make_pair (dist, rec);
}

/**
 * @brief 优化解决方案入口
 * @param p 长度为 i 的钢条的价格表
 * @param n 钢条长度
 * @return 返回最优收益和切割方案，即切割出的每段钢条的长度构成的数组
 */
std::pair<int, std::vector<int>> Solution (std::vector<int>& p, int n)
{
    int length = n;
    if (length < 0) return std::make_pair (0, std::vector<int> ());

    std::vector<int> ans;
    auto [dist, rec] = Cut_Rod (p, length);
    while (length > 0)
    {
        ans.push_back (rec[length]);
        length -= rec[length];
    }
    return std::make_pair (dist[n], ans);
}

int main ()
{
    std::vector<int> p = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    std::cout << "Price list\nlenght(inch) : ";
    for (int i = 0; i < p.size (); i++)
    {
        std::cout << i + 1 << '\t';
    }
    std::cout << "\nprice(dollar): ";
    for (int i = 0; i < p.size (); i++)
    {
        std::cout << p[i] << '\t';
    }
    std::cout << '\n';

    int n;
    std::cout << "Enter length > ";
    std::cin >> n;

    auto [optimalYield, scheme] = Solution (p, n);

    std::cout << "Optimal yield = " << optimalYield << std::endl;
    std::cout << "scheme = ";
    for (const auto& it : scheme)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}