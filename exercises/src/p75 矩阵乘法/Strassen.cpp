#include <iostream>
#include <vector>

// 矩阵相加
template<typename T>
std::vector<std::vector<T>> operator+(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B) 
{
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// 矩阵相减
template<typename T>
std::vector<std::vector<T>> operator-(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B) 
{
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// 矩阵乘法 Strassen方法
template<typename T>
std::vector<std::vector<T>> operator*(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B) 
{
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));

    if (n == 1) 
    {
        C[0][0] = A[0][0] * B[0][0];
    }
    else 
    {
        // 将矩阵分为四个子矩阵
        int half = n / 2;
        std::vector<std::vector<T>> A11(half, std::vector<T>(half));
        std::vector<std::vector<T>> A12(half, std::vector<T>(half));
        std::vector<std::vector<T>> A21(half, std::vector<T>(half));
        std::vector<std::vector<T>> A22(half, std::vector<T>(half));
        std::vector<std::vector<T>> B11(half, std::vector<T>(half));
        std::vector<std::vector<T>> B12(half, std::vector<T>(half));
        std::vector<std::vector<T>> B21(half, std::vector<T>(half));
        std::vector<std::vector<T>> B22(half, std::vector<T>(half));

        // 将原始矩阵的值拷贝到子矩阵中
        for (int i = 0; i < half; ++i) 
        {
            for (int j = 0; j < half; ++j) 
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + half];
                A21[i][j] = A[i + half][j];
                A22[i][j] = A[i + half][j + half];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + half];
                B21[i][j] = B[i + half][j];
                B22[i][j] = B[i + half][j + half];
            }
        }

        // Strassen算法的矩阵乘法公式
        std::vector<std::vector<T>> P1 = A11 * (B12 - B22);
        std::vector<std::vector<T>> P2 = (A11 + A12) * B22;
        std::vector<std::vector<T>> P3 = (A21 + A22) * B11;
        std::vector<std::vector<T>> P4 = A22 * (B21 - B11);
        std::vector<std::vector<T>> P5 = (A11 + A22) * (B11 + B22);
        std::vector<std::vector<T>> P6 = (A12 - A22) * (B21 + B22);
        std::vector<std::vector<T>> P7 = (A11 - A21) * (B11 + B12);

        // 计算结果的四个子矩阵
        std::vector<std::vector<T>> C11 = P5 + P4 - P2 + P6;
        std::vector<std::vector<T>> C12 = P1 + P2;
        std::vector<std::vector<T>> C21 = P3 + P4;
        std::vector<std::vector<T>> C22 = P5 + P1 - P3 - P7;

        // 将四个子矩阵合并为结果矩阵
        for (int i = 0; i < half; ++i)
        {
            for (int j = 0; j < half; ++j) 
            {
                C[i][j] = C11[i][j];
                C[i][j + half] = C12[i][j];
                C[i + half][j] = C21[i][j];
                C[i + half][j + half] = C22[i][j];
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