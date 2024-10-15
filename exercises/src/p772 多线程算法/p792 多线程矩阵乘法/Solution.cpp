#include <iostream>
#include <vector>
#include <thread>
#include <random>

#include "E:\Study\undergraduate\Develop\1.program\C++ program\3.algorithm\Introduction to Algorithms\Exercises\src\1.Benchmarking\Timer.h"

/* 串行版本 */
void matrixMultiply(const std::vector<std::vector<int>> &matrix1,
                    const std::vector<std::vector<int>> &matrix2,
                    std::vector<std::vector<int>> &result)
{
    int rows = matrix1.size();
    int cols = matrix2[0].size();
    int common = matrix2.size();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < common; ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

/* 并行版本 */
// 定义矩阵乘法的函数
void multiply(const std::vector<std::vector<int>> &matrix1,
              const std::vector<std::vector<int>> &matrix2,
              std::vector<std::vector<int>> &result,
              int row, int col, int common)
{
    for (int i = 0; i < common; ++i)
    {
        result[row][col] += matrix1[row][i] * matrix2[i][col];
    }
}

// 多线程矩阵乘法
void p_matrixMultiply(const std::vector<std::vector<int>> &matrix1,
                      const std::vector<std::vector<int>> &matrix2,
                      std::vector<std::vector<int>> &result)
{
    int rows = matrix1.size();
    int cols = matrix2[0].size();
    int common = matrix2.size();

    // 创建线程池
    std::vector<std::thread> threads;

    // 使用多线程进行矩阵乘法
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            threads.emplace_back(multiply, std::ref(matrix1), std::ref(matrix2), std::ref(result), i, j, common);
        }
    }

    // 等待所有线程完成
    for (auto &thread : threads)
    {
        thread.join();
    }
}

void getRandomMatrix(std::vector<std::vector<int>>& matrix, int min, int max)
{
    std::random_device rd; // 用于随机数引擎获得随机种子
    std::mt19937 gen(rd()); // 以 rd()为种子的标准 mersenne_twister_engine
    std::uniform_int_distribution<int> distribute(min, max);

    for(int i = 0; i < matrix.size(); ++i)
    {
        for(int j = 0; j < matrix[i].size(); ++j)
        {
            matrix[i][j] = distribute(gen);
        }
    }
}

void test_matrixMultiply(int i, int k, int j, int min, int max)
{
    std::vector<std::vector<int>> matrix1(i, std::vector<int>(k));
    getRandomMatrix(matrix1, min, max);
    std::vector<std::vector<int>> matrix2(k, std::vector<int>(j));
    getRandomMatrix(matrix2, min, max);

    std::vector<std::vector<int>> result1(matrix1.size(), std::vector<int>(matrix2[0].size(), 0));
    std::vector<std::vector<int>> result2(matrix1.size(), std::vector<int>(matrix2[0].size(), 0));

    {
        Timer timer("matrixMultiply");
        matrixMultiply(matrix1, matrix2, result2);
    }
}

void test_p_matrixMultiply(int i, int k, int j, int min, int max)
{
    std::vector<std::vector<int>> matrix1(i, std::vector<int>(k));
    getRandomMatrix(matrix1, min, max);
    std::vector<std::vector<int>> matrix2(k, std::vector<int>(j));
    getRandomMatrix(matrix2, min, max);

    std::vector<std::vector<int>> result1(matrix1.size(), std::vector<int>(matrix2[0].size(), 0));
    std::vector<std::vector<int>> result2(matrix1.size(), std::vector<int>(matrix2[0].size(), 0));

    {
        Timer timer("p_matrixMultiply");
        p_matrixMultiply(matrix1, matrix2, result1);
    }
}

int main()
{
    int k = 10;
    for(int i = 0; i < 100; ++i)
    {
        // std::cout << i << ' ' << k << ' ' << i << std::endl;
        test_matrixMultiply(i, k, i, -100, 100);
    }

    std::cout << "========================================\n";

    for(int i = 0; i < 100; ++i)
    {
        // std::cout << i << ' ' << k << ' ' << i << std::endl;
        test_p_matrixMultiply(i, k, i, -100, 100);
    }

    
    // for (const auto &row : result1)
    // {
    //     for (int val : row)
    //     {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (const auto &row : result2)
    // {
    //     for (int val : row)
    //     {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
