#include <iostream>
#include <limits>
#include <ctime>

#include "RBTree.h"

constexpr int SIZE = 20;

int main()
{
    RBTree<int, int> tree;
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < SIZE; i++)
    {
        tree.Insert(i, (int)(rand() % SIZE));
        tree.PrintTree();
        std::cout << "-------------------------------------------------------------\n";
    }
    tree.PrintTree();

    std::cout << "Minimum = " << *tree.Minimum() << std::endl;
    std::cout << "Maximum = " << *tree.Maximum() << std::endl;
    std::cout << "Size = " << tree.Size() << std::endl;
    std::cout << (tree.Empty() ? "tree empty" : "tree not empty") << std::endl;

    std::cout << "before    = ";
    for (RBTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    std::cout << "Preorder  = ";
    tree.Preorder();
    std::cout << "Postorder = ";
    tree.Postorder();

    tree.Delete(5);
    std::cout << "delete 5  = ";
    for (const auto &it : tree)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';
    std::cout << (tree.Has(5) ? "key 5 exist" : "key 5 not exist") << std::endl;
    std::cout << "Size = " << tree.Size() << std::endl;

    tree.Clear();
    std::cout << "Clear";
    for (const auto &it : tree)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';
    std::cout << "Size = " << tree.Size() << std::endl;
    std::cout << (tree.Empty() ? "tree empty" : "tree not empty") << std::endl;

    tree.Insert(1, 1);
    tree.PrintTree();
    return 0;
}
