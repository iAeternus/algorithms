/*
最长公共子串（Longest Common Substring）与最长公共子序列（Longest Common Subsequence）的区别：
子串要求在原字符串中是连续的，而子序列则只需保持相对顺序一致，并不要求连续。
例如
X = {a, Q, 1, 1}
Y = {a, 1, 1, d, f}
那么，{a, 1, 1}是X和Y的最长公共子序列，但不是它们的最长公共字串。
*/
#include <iostream>
#include <vector>

// 回溯方向
enum Backtrack
{
    Top_left, // 左上
    Left,     // 左
    Up,       // 上
};

/**
 * @brief 动态规划部分
 * @param X 串
 * @param Y 串
 * @return 返回 dp 数组和 rec 数组
*/
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<Backtrack>>>
LCS_Length(std::string& X, std::string& Y)
{
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<Backtrack>> rec(m + 1, std::vector<Backtrack>(n + 1));

    for(int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++) 
        {
            if(X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                rec[i][j] = Top_left;
            }
            else if(dp[i - 1][j] >= dp[i][j - 1])
            {
                dp[i][j] = dp[i - 1][j];
                rec[i][j] = Up;
            }
            else
            {
                dp[i][j] = dp[i][j - 1];
                rec[i][j] = Left;
            }
        }
    }
    return std::make_pair(dp, rec);
}

// 构造最优解
void Print_LCS(std::vector<std::vector<Backtrack>>& rec, std::string& X, int i, int j)
{
    if(!i || !j) return;

    if(rec[i][j] == Top_left)
    {
        Print_LCS(rec, X, i - 1, j - 1);
        std::cout << X[i - 1];
    }
    else if(rec[i][j] == Left)
    {
        Print_LCS(rec, X, i, j - 1);
    }
    else
    {
        Print_LCS(rec, X, i - 1, j);
    }
}

int main ()
{
    // 两件碱基序列，比较两 DNA 的相似性，结果为 GTCGTCGGAAGCCGGCCGAA
    std::string X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    std::string Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

    auto[dp, rec] = LCS_Length(X, Y);

    Print_LCS(rec, X, X.size(), Y.size());

    return 0;
}