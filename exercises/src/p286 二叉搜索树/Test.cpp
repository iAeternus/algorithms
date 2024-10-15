#include <iostream>
#include <ctime>

#include "Binary_search_tree.h"

constexpr int SIZE = 10;

int main()
{
    BSTree<int> tree;
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < SIZE; i++)
    {
        tree.Insert(rand() % SIZE);
    }

    std::cout << "Minimum = " << (*tree.Minimum()).data << std::endl;
    std::cout << "Maximum = " << (*tree.Maximum()).data << std::endl;
    std::cout << "Size = " << tree.Size() << std::endl;

    std::cout << "defore   = ";
    for (const auto& it : tree)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';

    std::cout << "Preorder = ";
    tree.Preorder();
    std::cout << "Postorder= ";
    tree.Postorder();

    tree.Delete(5);
    std::cout << "delete 5 = ";
    for (const auto& it : tree)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';
    std::cout << "Size = " << tree.Size() << std::endl;

    tree.Clear();
    std::cout << "Clear";
    for (const auto& it : tree)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';
    std::cout << "Size = " << tree.Size() << std::endl;

    return 0;
}
