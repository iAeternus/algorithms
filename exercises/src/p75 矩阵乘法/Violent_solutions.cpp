#include <iostream>
#include <vector>

/**
 * \brief 暴力求解  时间复杂度 O(n^3)
 * 
 * \param A n * n 的矩阵
 * \param B n * n 的矩阵
 * \return C = A * B
*/
template<typename T>
std::vector<std::vector<T>> operator *(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B)
{
    int n = A.size(); // 矩阵 A 的行数
    std::vector<std::vector<T>> C(n, std::vector<T>(n, 0)); // n * n
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main()
{
    std::vector<std::vector<int>> A = {
        {6, 3, 7, 1},
        {2, 5, 1, 7},
        {7, 5, 9, 1},
        {2, 6, 3, 4},
    };
    std::vector<std::vector<int>> B = {
        {1, 3, 2, 4},
        {1, 5, 3, 2},
        {4, 3, 2, 1},
        {5, 4, 5, 1},
    };
    std::vector<std::vector<int>> C = A * B;
    for(int i = 0; i < C.size(); i++)
    {
        for(int j = 0; j < C[i].size(); j++)
        {
            std::cout << C[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return 0;
}