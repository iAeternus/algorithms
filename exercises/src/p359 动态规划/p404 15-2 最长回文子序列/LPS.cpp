/*
leetcode same
516. 最长回文子序列
中等
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

示例 1：
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。

示例 2：
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。

提示：
1 <= s.length <= 1000
s 仅由小写英文字母组成
--------------------------------------------------
dp[i][j]：s[i..j] 的最长回文子序列长度为 dp[i][j]

如果我们想求 dp[i][j]，假设你知道了子问题 dp[i+1][j-1] 的结果（s[i+1..j-1] 中最长回文子序列的长度），
你是否能想办法算出 dp[i][j] 的值（s[i..j] 中，最长回文子序列的长度）呢？
可以！这取决于 s[i] 和 s[j] 的字符：
如果它俩相等，
那么它俩加上 s[i+1..j-1] 中的最长回文子序列就是 s[i..j] 的最长回文子序列：
如果它俩不相等，
说明它俩不可能同时出现在 s[i..j] 的最长回文子序列中，
那么把它俩分别加入 s[i..j-1] 和 s[i+1..j] 中，看看哪个子串产生的回文子序列更长即可

初始化，当 i == j 时，原串长度为 1，结果为 1
*/
#include <iostream>
#include <vector>
#include <string>

class Solution 
{
public:
    int longestPalindromeSubseq(std::string s) 
    {
        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        // 动态规划，反着遍历
        for(int i = n - 1; i >= 0; i--)
        {
            dp[i][i] = 1; // base case
            for(int j = i + 1; j < n; j++)
            {
                if(s[i] == s[j])
                {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else
                {
                    dp[i][j] = std::max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        // 整个 s 的最长回文子串长度
        return dp[0][n - 1];
    }
};

int main()
{
    Solution s;
    std::string str = "bbbab"; // 4
    std::cout << s.longestPalindromeSubseq(str) << std::endl;

    str = "cbbd"; // 2
    std::cout << s.longestPalindromeSubseq(str) << std::endl;
    return 0;
}