#include <iostream>
#include <vector>

#include "Priority_Queue.h"

int main()
{
    PQUEUE<int, int> queue;
    for(int i = 1; i <= 10; i++)
    {
        queue.Insert(i, i * 2);
    }
    std::pair<int, int> res = queue.Extract_Max();
    std::cout << "Extract max " << res.first << ' ' << res.second << std::endl;
    res = queue.Maximum();
    std::cout << "Current Max " << res.first << ' ' << res.second << std::endl;
    return 0;
}

