/*
Young氏矩阵是一种特殊的二维数据结构，它具有部分有序性质。以下是Young氏矩阵的实现思路、优缺点以及使用场景的详细说明：

实现思路：
Young氏矩阵是一个m×n的矩阵，其中每一行和每一列都按非递减（或非递增）顺序排列。
左上角的元素是矩阵中的最小（或最大）元素，右下角的元素是最大（或最小）元素。
Young氏矩阵可以使用二维数组或其他合适的数据结构来表示。

优点：
查找操作高效：由于矩阵中的元素按照特定的顺序排列，可以使用类似二分查找的方式在矩阵中进行查找，从而获得较高的查找效率。
插入和删除操作可控：通过控制元素的插入和删除位置，可以保持矩阵的有序性质。

缺点：
非动态扩展：Young氏矩阵的大小是固定的，一旦创建后，只能操作已有的元素，无法动态地扩展或缩小矩阵的大小。
空间浪费：如果矩阵的实际元素数量较少，但矩阵的大小较大，会造成空间的浪费。

使用场景：
有序集合：Young氏矩阵适用于需要维护一个有序集合的情况，可以高效地支持元素的查找、插入和删除操作。
优先级队列：Young氏矩阵可用作优先级队列的底层数据结构，可以实现高效地插入和删除最小（或最大）元素的操作。

需要注意的是，Young氏矩阵在实际应用中并不常见，因为它有一些限制，如固定大小和空间浪费。
在大多数情况下，人们更倾向于使用其他数据结构，如二叉堆、二叉搜索树或跳表，来实现类似的功能。
这些数据结构具有更灵活的大小调整和更高的空间利用率。
*/
#include <iostream>
#include <vector>

class YoungMatrix
{
private:
    std::vector<std::vector<int>> matrix;
    int rows;
    int cols;

public:
    YoungMatrix(int m, int n) : rows(m), cols(n)
    {
        matrix.resize(m, std::vector<int>(n, std::numeric_limits<int>::max())); // 初始化矩阵中所有元素为无穷大
    }

    bool IsEmpty() const
    {
        return matrix[0][0] == std::numeric_limits<int>::max();

    }

    bool IsFull() const
    {
        return matrix[rows - 1][cols - 1] < std::numeric_limits<int>::max();
    }

    void Insert(int value, int row, int col)
    {
        if (row >= rows || col >= cols)
            return;

        if (value >= matrix[row][col])
        {
            if (col + 1 < cols)
            {
                Insert(value, row, col + 1);  // 向右移动
            }
            else if (row + 1 < rows)
            {
                Insert(value, row + 1, col);  // 向下移动
            }
            else
            {
                matrix[row][col] = value;
            }
        }
        else
        {
            std::swap(value, matrix[row][col]);  // 交换插入值和当前位置的值
            Insert(value, row, col);  // 继续向左移动
        }
    }

    void Insert(int value)
    {
        if (IsFull())
        {
            std::cout << "Young matrix is full" << std::endl;
            return;
        }

        Insert(value, 0, 0);
    }

    int Extract_min()
    {
        if (IsEmpty())
        {
            std::cout << "Young matrix is empty" << std::endl;
            return std::numeric_limits<int>::max();
        }

        int min_value = matrix[0][0];
        matrix[0][0] = std::numeric_limits<int>::max();

        int i = 0;
        int j = 0;
        while (true)
        {
            int next_row = -1;
            int next_col = -1;

            // 寻找下一个要下沉的位置
            if (i + 1 < rows && matrix[i + 1][j] < matrix[i][j])
            {
                next_row = i + 1;
                next_col = j;
            }

            if (j + 1 < cols && matrix[i][j + 1] < matrix[i][j])
            {
                next_row = i;
                next_col = j + 1;
            }

            // 如果找到下一个要下沉的位置，则进行下沉操作
            if (next_row != -1 && next_col != -1)
            {
                std::swap(matrix[next_row][next_col], matrix[i][j]);
                i = next_row;
                j = next_col;
            }
            else
            {
                // 如果没有找到下一个要下沉的位置，则维持Young矩阵的性质完成
                break;
            }
        }

        return min_value;
    }

    bool Search(int value)
    {
        int i = 0;
        int j = cols - 1;

        // 从右上角开始比较，根据大小关系进行移动
        while (i <= rows - 1 && j >= 0)
        {
            if (matrix[i][j] == value)
            {
                return true;
            }
            else if (matrix[i][j] < value)
            {
                i++;
            }
            else
            {
                j--;
            }
        }

        return false;
    }

    void Print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (matrix[i][j] == std::numeric_limits<int>::max())
                {
                    std::cout << "- ";
                }
                else
                {
                    std::cout << matrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};