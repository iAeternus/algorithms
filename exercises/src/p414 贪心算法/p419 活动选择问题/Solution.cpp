/*
假定有集合S个活动 S = {a1,a2,a2...an}，
对于每个活动的开始与结束时间为 s = {s1,s2,s3...sn}, f = {f1,f2,f3..fn};
求在不重复时间段里可以利用的场地最大化（活动最多）的解。
---------------------------------------------------
首先按结束时间对活动排序
选取第一个活动（贪心选择，给后面的活动预留最大的空间）
选取第一个活动之后第一个开始的活动，以此类推
*/
#include <iostream>
#include <algorithm>
#include <vector>

struct Program
{
    int start, end;

    Program(int start = 0, int end = 0) : start(start), end(end) {}
    Program(const Program& other) : start(other.start), end(other.end) {}
    Program& operator=(const Program& other)
    {
        if (this != &other)
        {
            start = other.start;
            end = other.end;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Program& program)
    {
        out << program.start << ' ' << program.end;
        return out;
    }
};

std::vector<Program> Greedy_Activity_Selector(std::vector<Program>& programs)
{
    std::sort(programs.begin(), programs.end(), [](const Program& a, const Program& b)->bool {
        return a.end < b.end;
        });

    std::vector<Program> result;
    result.push_back(programs[0]);
    int index = 0;

    for (int i = 1; i < programs.size(); i++)
    {
        if (programs[i].start >= programs[index].end)
        {
            result.push_back(programs[i]);
            index = i;
        }
    }

    return result;
}

int main()
{
    std::vector<Program> programs = {
        {1, 4},
        {3, 5},
        {0, 6},
        {5, 7},
        {3, 9},
        {5, 9},
        {6, 10},
        {8, 11},
        {8, 12},
        {2, 14},
        {12, 16},
    };

    std::vector<Program> result = Greedy_Activity_Selector(programs);

    for (const auto& it : result)
    {
        std::cout << it << std::endl;
    }

    return 0;
}