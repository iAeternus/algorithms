#include <iostream>

#include "Interval_Tree.h"

int main ()
{
    IntTree<int> tree;
    tree.Insert (Interval<int> (16, 21)); // 测试用例 p348 
    tree.Insert (Interval<int> (8, 9));
    tree.Insert (Interval<int> (25, 30));
    tree.Insert (Interval<int> (5, 8));
    tree.Insert (Interval<int> (15, 23));
    tree.Insert (Interval<int> (17, 19));
    tree.Insert (Interval<int> (26, 26));
    tree.Insert (Interval<int> (0, 3));
    tree.Insert (Interval<int> (6, 10));
    tree.Insert (Interval<int> (19, 20));
    tree.PrintTree ();
    std::cout << "------------------------------------------\n";
    //tree.Delete(Interval<int>(16, 21));
    //tree.PrintTree();

    Interval<int> i; // 11 14 -> 不存在
    std::cout << "Enter i > ";
    std::cin >> i;
    std::cout << *tree.Search (i) << std::endl;

    return 0;
}