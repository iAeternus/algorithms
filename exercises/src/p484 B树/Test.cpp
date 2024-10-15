#include <iostream>

#include "B-Tree.h"

int main()
{
    BTree<char> tree;
    for(char ch = 'A'; ch <= 'Z'; ch++)
    {
        tree.Insert(ch);
    }
    tree.PrintBTree();
    return 0;
}