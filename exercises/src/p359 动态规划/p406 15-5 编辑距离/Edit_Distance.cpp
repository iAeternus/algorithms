/*
最小编辑距离问题 MED
输入：长度为 n 的字符串 s，长度为 m 的字符串 t
输出：求出一组编辑操作 O = < e1, e2,..., ed >，令 min | O | (优化目标)
约束条件：s.t.字符串 s 经过 O 的操作后满足 s == t
*/
#include <iostream>
#include <string>
#include <vector>

enum Operate { LU, U, L }; // 替换、删除、插入

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<Operate>>> MED(std::string& S, std::string& T)
{
    int n = S.size();
    int m = T.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    std::vector<std::vector<Operate>> rec(n + 1, std::vector<Operate>(m + 1));
    for (int i = 0; i <= n; i++) // 纵向初始化
    {
        dp[i][0] = i;
        rec[i][0] = U;
    }
    for (int j = 0; j <= m; j++) // 横向初始化
    {
        dp[0][j] = j;
        rec[0][j] = L;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int replace = dp[i - 1][j - 1] + (S[i - 1] != T[j - 1] ? 1 : 0); // 替换
            int remove = dp[i - 1][j] + 1; // 删除
            int insert = dp[i][j - 1] + 1; // 插入

            if (replace <= remove && replace <= insert)
            {
                dp[i][j] = replace;
                rec[i][j] = LU;
            }
            else if (remove < replace && remove <= insert)
            {
                dp[i][j] = remove;
                rec[i][j] = U;
            }
            else
            {
                dp[i][j] = insert;
                rec[i][j] = L;
            }
        }
    }

    return std::make_pair(dp, rec);
}

void Print_MED(std::vector<std::vector<Operate>>& rec, std::string& S, std::string& T)
{
    int i = S.size();
    int j = T.size();

    while (i > 0 || j > 0) // 为了避免操作时字符串的索引发生偏移，使用迭代而不是递归
    {
        if (rec[i][j] == LU)
        {
            if (S[i - 1] != T[j - 1])
            {
                std::cout << "Replace " << S[i - 1] << " with " << T[j - 1] << std::endl;
                S[i - 1] = T[j - 1]; // 替换操作
            }
            i--;
            j--;
        }
        else if (rec[i][j] == U)
        {
            std::cout << "Delete " << S[i - 1] << std::endl;
            S.erase(i - 1, 1); // 删除操作
            i--;
        }
        else if (rec[i][j] == L)
        {
            std::cout << "Insert " << T[j - 1] << std::endl;
            S.insert(i, 1, T[j - 1]); // 插入操作
            j--;
        }
    }
}
int main()
{
    std::string S = "algorithm";
    std::string T = "altruistic";

    auto[dp, rec] = MED(S, T);
    std::cout << "S = " << S << std::endl;
    std::cout << "T = " << T << std::endl;
    std::cout << "Minimum Edit Distance: " << dp[S.size()][T.size()] << std::endl;
    std::cout << "Edit Operation Sequence:" << std::endl;
    Print_MED(rec, S, T);
    std::cout << "result: \n";
    std::cout << "S = " << S << std::endl;
    std::cout << "T = " << T << std::endl;

    std::cout << "---------------------------------------\n";

    S = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    T = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    auto[dp1, rec1] = MED(S, T);
    std::cout << "S = " << S << std::endl;
    std::cout << "T = " << T << std::endl;
    std::cout << "Minimum Edit Distance: " << dp1[S.size()][T.size()] << std::endl;
    std::cout << "Edit Operation Sequence:" << std::endl;
    Print_MED(rec1, S, T);
    std::cout << "result: \n";
    std::cout << "S = " << S << std::endl;
    std::cout << "T = " << T << std::endl;

    return 0;
}