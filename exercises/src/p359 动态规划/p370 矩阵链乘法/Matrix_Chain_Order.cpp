#include <iostream>
#include <vector>
#include <limits>

#include "../../1.Benchmarking/Timer.h"

// const std::string RED_COLOR_CODE = "\033[1;31m";  // 设置文本颜色为红色的ANSI转义码
// const std::string DEFAULT_COLOR_CODE = "\033[0m"; // 恢复默认文本颜色的ANSI转义码

/**
 * @brief 动态规划部分
 * @param p 矩阵 A[i] 的规模为 p[i - 1] * p[i]
 * @return 返回标量乘法的最小次数和追踪数组
 */
std::pair<int, std::vector<std::vector<int>>> Matrix_Chain_Order(std::vector<int> &p)
{
    int n = p.size() - 1;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));  // 备忘录数组
    std::vector<std::vector<int>> rec(n + 1, std::vector<int>(n + 1, 0)); // 追踪数组

    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            dp[i][j] = std::numeric_limits<int>::max();
            for (int k = i; k < j; k++)
            {
                int q = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < dp[i][j])
                {
                    dp[i][j] = q;
                    rec[i][j] = k;
                }
            }
        }
    }
    return std::make_pair(dp[1][n], rec);
}

// 构造最优解
void Print_Optimal_Parens(std::vector<std::vector<int>> &rec, int i, int j)
{
    if (i == j)
    {
        std::cout << "A[" << i << ']';
    }
    else
    {
        std::cout << RED_COLOR_CODE << '(' << DEFAULT_COLOR_CODE;
        Print_Optimal_Parens(rec, i, rec[i][j]);
        Print_Optimal_Parens(rec, rec[i][j] + 1, j);
        std::cout << RED_COLOR_CODE << ')' << DEFAULT_COLOR_CODE;
    }
}

void Print_Optimal_Parens(std::vector<int> &p, std::vector<std::vector<int>> &rec)
{
    Print_Optimal_Parens(rec, 1, p.size() - 1);
}

void Test(std::vector<int> &p)
{
    std::pair<int, std::vector<std::vector<int>>> res;

    Timer::automatic_measurement_of_time([&]() -> void {
        res = Matrix_Chain_Order(p);
    }, "Matrix_Chain_Order", 10000);

    std::cout << "The least scalar multiplication times = " << res.first << std::endl;
    Print_Optimal_Parens(p, res.second);
    std::cout << std::endl;
}

int main()
{
    std::vector<int> p1 = {30, 35, 15, 5, 10, 20, 25}; // p375
    Test(p1);

    std::vector<int> p2 = {5, 10, 3, 12, 5, 50, 6}; // p377 15.2-1
    Test(p2);

    return 0;
}