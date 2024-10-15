/**
 * @brief 二叉搜索树类型定义
 * @brief 插入、删除、查找操作时间复杂度均为 O(h) (h为树高)
 * @author Ricky
 * @date 2023/7/28
*/
#pragma once

template<typename Object>
class BSTree
{
public:
    // 二叉搜索树节点定义
    struct Node
    {
        Object data; // 数据域
        Node* parent; // 父亲指针
        Node* left; // 左孩子
        Node* right; // 右孩子

        Node(const Object& data, Node* const parent = nullptr, Node* const left = nullptr, Node* const right = nullptr)
            : data(data), parent(parent), left(left), right(right) {}
    };

    // 二叉搜索树迭代器定义
    class Iterator
    {
    public:
        Iterator(Node* const current = nullptr) : current(current) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator++()
        {
            current = BSTree::Successor(current);
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

        Object& operator*() const { return current->data; }
        Object* operator->() const { return &current->data; }
    private:
        Node* current;
        friend class BSTree;
    };

    Iterator begin() { return Iterator(Minimum(root)); }
    Iterator end() { return Iterator(nullptr); }

    BSTree() : root(nullptr), size(0) {}
    virtual ~BSTree() { Clear(); }

    // 功能函数
    // 查询最小元
    Node* Minimum() const { return Minimum(root); }
    // 查询最大元
    Node* Maximum() const { return Maximum(root); }
    // 查询树的大小
    int Size() const { return size; }

    // 查找，找不到返回 nullptr
    Node* Search(const Object& object) const
    {
        Node* p = Iterative_Tree_Search(root, object);
        return p != root ? p : nullptr;
    }

    // 遍历打印整棵树
    void Preorder() const { Preorder(root); std::cout << '\n'; }
    void InOrder() const { InOrder(root); std::cout << '\n'; }
    void Postorder() const { Postorder(root); std::cout << '\n'; }

    // 插入
    void Insert(const Object& object)
    {
        Node* prev = nullptr;
        Node* ins = root;
        while (ins)
        {
            prev = ins;
            if (object < ins->data)
            {
                ins = ins->left;
            }
            else
            {
                ins = ins->right;
            }
        }
        Node* newNode = new Node(object, prev);
        if (!prev) // 树空
        {
            root = newNode;
        }
        else if (newNode->data < prev->data) // 应该连在左边
        {
            prev->left = newNode;
        }
        else // 应该连在右边
        {
            prev->right = newNode;
        }
        ++size;
    }

    // 删除
    void Delete(const Object& object)
    {
        Node* deleteNode = Iterative_Tree_Search(root, object);
        if (!deleteNode) return;

        if (!deleteNode->left)
        {
            Transplant(deleteNode, deleteNode->right);
            delete deleteNode;
        }
        else if (!deleteNode->right)
        {
            Transplant(deleteNode, deleteNode->left);
            delete deleteNode;
        }
        else
        {
            Node* y = Minimum(deleteNode->right);
            if (y->parent != deleteNode) // 将后继提到要删除的节点的右孩子那里，让其后继接管右子树
            {
                Transplant(y, y->right);
                y->right = deleteNode->right;
                y->right->parent = y;
            }
            Transplant(deleteNode, y); // 用后继覆盖要删除的节点，让新根节点接管左子树
            y->left = deleteNode->left;
            y->left->parent = y;
            delete deleteNode;
        }
        --size;
    }

    // 清空
    void Clear()
    {
        Clear(root);
        root = nullptr;
    }

protected:
    Node* root; // 根节点
    int size; // 节点个数

    // 查询以 x 为根节点的树的最小元
    static Node* Minimum(Node* x)
    {
        while (x && x->left)
        {
            x = x->left;
        }
        return x;
    }

    // 查询以 x 为根节点的树的最大元
    static Node* Maximum(Node* x)
    {
        while (x && x->right)
        {
            x = x->right;
        }
        return x;
    }

    // 返回 x 的后继
    static Node* Successor(Node* x)
    {
        // 节点右子树非空，后继为右子树中的最左节点（最小节点）
        if (x->right)
        {
            return Minimum(x->right);
        }
        Node* y = x->parent;
        while (y && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // 在以 x 为根的子树中查找 k
    Node* Iterative_Tree_Search(Node* x, const Object& k) const
    {
        while (x && k != x->data)
        {
            if (k < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        return x;
    }

    // 前序遍历以 x 为根节点的子树
    void Preorder(Node* const x) const
    {
        if (x)
        {
            std::cout << x->data << ' ';
            Preorder(x->left);
            Preorder(x->right);
        }
    }

    // 中序遍历以 x 为根节点的子树
    void InOrder(Node* const x) const
    {
        if (x)
        {
            InOrder(x->left);
            std::cout << x->data << ' ';
            InOrder(x->right);
        }
    }

    // 后序遍历以 x 为根节点的子树
    void Postorder(Node* const x) const
    {
        if (x)
        {
            Postorder(x->left);
            Postorder(x->right);
            std::cout << x->data << ' ';
        }
    }

    // 用一棵以 v 为根的子树替换以 u 为根的子树，并成为后者父亲的孩子结点
    void Transplant(Node* u, Node* v)
    {
        if (!u->parent)
        {
            root = v;
        }
        else if (u->parent->left == u)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        if (v)
        {
            v->parent = u->parent;
        }
    }

    // 清空以 x 为根的子树
    void Clear(Node* x)
    {
        if (x)
        {
            Clear(x->left);
            x->left = nullptr;
            Clear(x->right);
            x->right = nullptr;
            delete x;
        }
        size = 0;
    }
};