#include <iostream>
#include <vector>

class MazeSolver
{
private:
    int m;  // 迷宫的行数
    int n;  // 迷宫的列数
    std::vector<std::vector<char>> maze;  // 迷宫数组
    std::vector<std::vector<bool>> visited;  // 记录节点是否访问过

public:
    MazeSolver (int rows, int cols) : m (rows), n (cols)
    {
        maze.resize (m, std::vector<char> (n));
        visited.resize (m, std::vector<bool> (n, false));
    }

    void readMaze ()
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cin >> maze[i][j];
            }
        }
    }

    bool solveMaze (int startRow, int startCol, int endRow, int endCol)
    {
        // 深度优先搜索(回溯)
        if (startRow == endRow && startCol == endCol)
        {
            maze[startRow][startCol] = '*';  // 标记终点为通道经过的空地
            return true;  // 找到终点，返回成功
        }

        visited[startRow][startCol] = 1;  // 标记当前节点为已访问

        // 按东、南、西、北的顺序进行探索
        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (int k = 0; k < 4; k++)
        {
            int nextRow = startRow + directions[k].first;
            int nextCol = startCol + directions[k].second;

            // 判断下一个节点是否可行走且未访问过
            if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n &&
                maze[nextRow][nextCol] == '.' && !visited[nextRow][nextCol])
            {
                if (solveMaze (nextRow, nextCol, endRow, endCol))
                {
                    maze[startRow][startCol] = '*';  // 标记当前节点为通道经过的空地
                    return true;  // 找到通路，返回成功
                }
                else
                {
                    maze[startRow][startCol] = 'o';  // 走不通而退回时经过的空地
                }
            }
        }

        return false;  // 未找到通路，返回失败
    }

    void printMaze ()
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (maze[i][j] == 'o')
                {
                    std::cout << 'o' << ' ';
                }
                else
                {
                    std::cout << maze[i][j] << ' ';
                }
            }
            std::cout << '\n';
        }
    }
};

int main ()
{
    int rows, cols;
    std::cin >> rows >> cols;

    MazeSolver solver (rows, cols);
    solver.readMaze ();

    int startRow, startCol, endRow, endCol;
    std::cin >> startRow >> startCol;
    std::cin >> endRow >> endCol;

    if (solver.solveMaze (startRow, startCol, endRow, endCol))
    {
        solver.printMaze ();
    }
    else
    {
        std::cout << "None\n";
    }

    return 0;
}