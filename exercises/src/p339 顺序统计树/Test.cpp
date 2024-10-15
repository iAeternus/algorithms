#include <iostream>
#include <string>
#include <ctime>

#include "Order_Statistic_Tree.h"

constexpr int SIZE = 10;

int main ()
{
    OSTree<int, int> tree;
    int i;
    for (i = 0; i < SIZE; i++)
    {
        tree.Insert (i, i * 2);
    }

    tree.PrintTree ();
    for (OSTree<int, int>::stIterator it = tree.begin (); it != tree.end (); it++)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Enter i > ";
    std::cin >> i;

    OSTree<int, int>::node_t* p = tree.Select (i);
    std::cout << "node = " << *p << std::endl;
    std::cout << "rank = " << tree.Rank (p->key) << std::endl;
    std::cout << "median = " << *tree.Median () << std::endl;

    return 0;
}
