#include <iostream>
#include <memory>

const int minDegree = 2;

template<typename keyType>
struct Node
{
    int numKeys;                     // 节点包含的有效键的数量
    keyType keys[(2 * minDegree) - 1];  // 存储键的数组
    std::unique_ptr<Node<keyType>> children[2 * minDegree];  // 存储子节点的智能指针数组
    bool leaf;                       // 标识是否为叶子节点

    Node ()
    {
        numKeys = 0;
        leaf = true;
    }
};

template<typename keyType>
class BTree
{
private:
    std::unique_ptr<Node<keyType>> root;  // 根节点智能指针

public:
    BTree ()
    {
        root = nullptr;
    }

    // 插入节点
    void Insert (const keyType& key)
    {
        if (root == nullptr)
        {
            root = std::make_unique<Node<keyType>> ();
            root->numKeys = 1;
            root->keys[0] = key;
        }
        else
        {
            if (root->numKeys == (2 * minDegree) - 1)
            {  // 根节点已满，需要分裂
                std::unique_ptr<Node<keyType>> newRoot = std::make_unique<Node<keyType>> ();
                newRoot->numKeys = 0;
                newRoot->children[0] = std::move (root);
                SplitChild (newRoot, 0);
                root = std::move (newRoot);
            }
            InsertNonFull (root.get (), key);
        }
    }

    // 删除节点
    void Delete (const keyType& key)
    {
        if (root == nullptr)
        {
            std::cout << "Error: The tree is empty." << std::endl;
            return;
        }
        if (root->numKeys == 0)
        {
            if (root->leaf)
            {
                root = nullptr;
            }
            else
            {
                root = std::move (root->children[0]);
            }
        }
        DeleteKey (root.get (), key);
    }

    // 打印B树结构
    void Print ()
    {
        if (root == nullptr)
        {
            std::cout << "Empty tree." << std::endl;
            return;
        }
        PrintTree (root.get (), "");
    }

private:
    // 分裂子节点
    void SplitChild (std::unique_ptr<Node<keyType>>& parent, int childIndex)
    {
        Node<keyType>* child = parent->children[childIndex].get ();
        std::unique_ptr<Node<keyType>> newNode = std::make_unique<Node<keyType>> ();
        newNode->numKeys = minDegree - 1;
        newNode->leaf = child->leaf;

        // 将后半部分键值移动到新节点
        for (int i = 0; i < minDegree - 1; ++i)
        {
            newNode->keys[i] = child->keys[i + minDegree];
        }

        // 如果非叶子节点，也需要移动子节点
        if (!child->leaf)
        {
            for (int i = 0; i < minDegree; ++i)
            {
                newNode->children[i] = std::move (child->children[i + minDegree]);
            }
        }

        // 调整子节点数量
        child->numKeys = minDegree - 1;

        // 将父节点键值和子节点指针空出位置
        for (int i = parent->numKeys; i > childIndex; --i)
        {
            parent->children[i + 1] = std::move (parent->children[i]);
        }
        for (int i = parent->numKeys - 1; i >= childIndex; --i)
        {
            parent->keys[i + 1] = parent->keys[i];
        }

        // 插入新节点的键值和指针
        parent->keys[childIndex] = child->keys[minDegree - 1];
        parent->children[childIndex + 1] = std::move (newNode);
        ++parent->numKeys;
    }

    // 在非满节点中插入关键字
    void InsertNonFull (Node<keyType>* node, const keyType& key)
    {
        int i = node->numKeys - 1;

        if (node->leaf)
        {
            while (i >= 0 && key < node->keys[i])
            {
                node->keys[i + 1] = node->keys[i];
                --i;
            }
            node->keys[i + 1] = key;
            ++node->numKeys;
        }
        else
        {
            while (i >= 0 && key < node->keys[i])
            {
                --i;
            }
            ++i;
            if (node->children[i]->numKeys == (2 * minDegree) - 1)
            {
                SplitChild (node, i);
                if (key > node->keys[i])
                {
                    ++i;
                }
            }
            InsertNonFull (node->children[i].get (), key);
        }
    }

    // 在树中查找并删除关键字
    void DeleteKey (Node<keyType>* node, const keyType& key)
    {
        int i = 0;
        while (i < node->numKeys && key > node->keys[i])
        {
            ++i;
        }

        if (i < node->numKeys && key == node->keys[i])
        {
            if (node->leaf)
            {
                for (int j = i; j < node->numKeys - 1; ++j)
                {
                    node->keys[j] = node->keys[j + 1];
                }
                --node->numKeys;
            }
            else
            {
                Node<keyType>* pred = node->children[i].get ();
                Node<keyType>* succ = node->children[i + 1].get ();

                if (pred->numKeys >= minDegree)
                {
                    keyType predKey = GetPredecessor (pred);
                    DeleteKey (pred, predKey);
                    node->keys[i] = predKey;
                }
                else if (succ->numKeys >= minDegree)
                {
                    keyType succKey = GetSuccessor (succ);
                    DeleteKey (succ, succKey);
                    node->keys[i] = succKey;
                }
                else
                {
                    MergeChildren (node, i);
                    DeleteKey (pred, key);
                }
            }
        }
        else
        {
            if (node->leaf)
            {
                std::cout << "Error: Key not found." << std::endl;
                return;
            }

            bool shouldMerge = false;
            int childIndex = 0;
            if (i == node->numKeys || key < node->keys[i])
            {
                childIndex = i;
                shouldMerge = (node->children[childIndex]->numKeys == minDegree - 1);
            }
            else
            {
                childIndex = i + 1;
                shouldMerge = (node->children[childIndex]->numKeys == minDegree - 1);
            }

            if (shouldMerge)
            {
                MergeChildren (node, childIndex);
            }
            DeleteKey (node->children[childIndex].get (), key);
        }
    }

    // 合并子节点
    void MergeChildren (Node<keyType>* node, int childIndex)
    {
        Node<keyType>* leftChild = node->children[childIndex].get ();
        Node<keyType>* rightChild = node->children[childIndex + 1].get ();

        // 将父节点的键值和右子节点的键值合并到左子节点
        leftChild->keys[minDegree - 1] = node->keys[childIndex];
        for (int i = 0; i < rightChild->numKeys; ++i)
        {
            leftChild->keys[i + minDegree] = rightChild->keys[i];
        }
        if (!leftChild->leaf)
        {
            for (int i = 0; i <= rightChild->numKeys; ++i)
            {
                leftChild->children[i + minDegree] = std::move (rightChild->children[i]);
            }
        }

        // 移动后续键值和子节点
        for (int i = childIndex + 1; i < node->numKeys; ++i)
        {
            node->keys[i - 1] = node->keys[i];
        }
        for (int i = childIndex + 2; i <= node->numKeys; ++i)
        {
            node->children[i - 1] = std::move (node->children[i]);
        }

        // 调整子节点的数量
        --node->numKeys;

        // 释放右子节点的内存
        rightChild = nullptr;
    }

    // 获取前驱键值
    keyType GetPredecessor (Node<keyType>* node)
    {
        while (!node->leaf)
        {
            node = node->children[node->numKeys].get ();
        }
        return node->keys[node->numKeys - 1];
    }

    // 获取后继键值
    keyType GetSuccessor (Node<keyType>* node)
    {
        while (!node->leaf)
        {
            node = node->children[0].get ();
        }
        return node->keys[0];
    }

    // 打印B树结构
    void PrintTree (Node<keyType>* node, const std::string& indent)
    {
        std::cout << indent;
        for (int i = 0; i < node->numKeys; ++i)
        {
            std::cout << node->keys[i] << " ";
        }
        std::cout << std::endl;

        if (!node->leaf)
        {
            for (int i = 0; i <= node->numKeys; ++i)
            {
                PrintTree (node->children[i].get (), indent + "  ");
            }
        }
    }
};

int main ()
{
    BTree<int> btree;
    btree.Insert (10);
    btree.Insert (20);
    btree.Insert (5);
    btree.Insert (15);
    btree.Insert (30);
    btree.Insert (25);
    btree.Insert (35);

    std::cout << "BTree structure: " << std::endl;
    btree.Print ();

    btree.Delete (20);
    btree.Delete (5);

    std::cout << "BTree structure after deletion: " << std::endl;
    btree.Print ();

    return 0;
}