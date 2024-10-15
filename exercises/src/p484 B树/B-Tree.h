/**
 * @brief B-树类型
 * @brief 与磁盘访问紧密联系的树，要检查的结点数比红黑树少大约 lgt 个因子，可避免大量磁盘访问
 * @author Ricky
 * @date 2023/7/30
 * @version 1.0
*/

// B-树类型定义，存储关键字
template<typename keyType>
class BTree
{
public:
    // 结点关键字个数上下界
    constexpr static size_t minDegree = 3; // 下界，值越大，B-树高度越小，节点最大关键字数 = 2 * 最小度数 - 1

    // B-树结点定义
    struct BTreeNode
    {
        size_t n; // 存储在结点中的关键字个数
        bool leaf; // 叶结点-true 内部节点-false
        keyType* keys; // 升序关键字数组，大小为 n
        BTreeNode** childrens; // 存放指向其孩子的指针，大小为 n + 1（注：叶结点无孩子）

        BTreeNode (size_t n = 0, bool leaf = true)
            : n (n), leaf (leaf), keys (new keyType[n]), childrens (new BTreeNode*[n + 1])
        {}
        BTreeNode (const BTreeNode& other)
            : n (other.n), leaf (other.leaf), keys (new keyType[n]), childrens (new BTreeNode*[n + 1])
        {
            int i;
            for (i = 0; i < n; i++)
            {
                keys[i] = other.keys[i];
                childrens[i] = other.childrens[i];
            }
            childrens[i++] = other.childrens[i];
        }
    };
    using node_t = BTreeNode;
protected:
    node_t* root; // 根节点
    int size; // 节点个数
public:
    // 实际暴露出来的公有函数
    BTree () : root (new node_t(0, true)), size (0) {}
    ~BTree ()
    {
        Clear ();
        delete root;
        root = nullptr;
    }

    /**
     * @brief 清空 B 树
    */
    void Clear ()
    {
        Release (root);
        size = 0;
    }

    /**
     * @brief 搜索 B 树
     * @param key 要搜索的关键字
     * @return 返回结点 y 和使得 y.key[i] == k 的下标 i 组成的有序对 (y, i)，否则返回 nullptr
    */
    std::pair<node_t*, int> Search (const keyType& key) const
    {
        return Search(root, key);
    }

    /**
     * @brief 插入一个关键字
     * @param key 要插入的关键字
     * @return 成功操作返回 true，否则返回 false
    */
    bool Insert (const keyType& key)
    {
        bool ret = true;
        node_t* r = root;
        if(r->n == 2 * minDegree - 1)
        {
            node_t* s = new node_t(0, false);
            root = s;
            s->childrens[0] = r;
            Split_Child(s, 1);
            Insert_nonFull(s, key);
        }
        else
        {
            Insert_nonFull(r, key);
        }
        return ret;
    }

    /**
     * @brief 从 B 树中删除关键字
     * @param key 要删除的关键字
     * @return 成功操作返回 true，否则返回 false
    */
    bool Delete (const keyType& key)
    {
        bool ret = true;
        return ret;
    }

    /**
     * @brief 打印树结构
    */
    void PrintBTree() const
    {
        PrintBTree(root, 0);
    }
private:
    // 辅助函数
    // 释放内存
    void Release (node_t* node)
    {
        if(!node)
        {
            return;
        }

        if(!node->leaf)
        {
            for(int i = 0; i < node->n + 1; i++)
            {
                Release(node->childrens[i]);
            }
        }
        delete node;
    }

    // 在以 node 为根的子树中搜索关键字 key
    std::pair<node_t*, int> Search (node_t* node, const keyType& key) const
    {
        int i = 0;
        while(i <= node->n && key > node->keys[i])
        {
            ++i;
        }
        if(i <= node->n && key == node.keys[i])
        {
            return std::make_pair(node, i);
        }
        else if(node->leaf)
        {
            return std::make_pair(nullptr, -1);
        }
        else
        {
            return Search(node->childrens[i], key);
        }
    }

    /**
     * @brief 分裂 B 树中的节点
     * @param node 非满的内部节点
     * @param i 使 node.childrens[i] 为 node 的满子节点的下标 i
    */
    void Split_Child(node_t* node, int i)
    {
        node_t* y = node->childrens[i];
        node_t* z = new node_t(minDegree - 1, y->leaf);

        // 将 y 的右半部分复制到 z
        for(int j = 0; j < minDegree - 1; j++)
        {
            z->keys[j] = y->keys[j + minDegree];
        }

        if(!y->leaf)
        {
            // 将 y 的右半部分的子节点复制到 z
            for(int j = 0; j < minDegree; j++)
            {
                z->childrens[j] = y->childrens[j + minDegree];
            }
        }
        
        // 更新 y 的键和子节点数量
        y->n = minDegree - 1;

        // 移动 node 中的键以腾出空间插入 z 的键
        for(int j = node->n; j >= i + 1; j--)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[i] = y->keys[minDegree - 1]; // 将 y 最中间的键插入 node
        ++node->n;

        // 插入 z 作为 node 的子节点
        for(int j = node->n; j >= i + 2; j--)
        {
            node->childrens[j] = node->childrens[j - 1];
        }
        node->childrens[i + 1] = z;
    }

    // 对非满的节点进行插入操作
    void Insert_nonFull(node_t* node, const keyType& key)
    {
        int i = node->n;
        if(node->leaf)
        {
            while(i >= 1 && key < node->keys[i])
            {
                node->keys[i + 1] = node->keys[i];
                --i;
            }
            node->keys[i + 1] = key;
            ++node->n;
        }
        else
        {
            while(i >= 0 && key < node->keys[i])
            {
                --i;
            }
            ++i;
            if(node->childrens[i]->n == 2 * minDegree - 1)
            {
                Split_Child(node, i);
                if(key > node->keys[i])
                {
                    ++i;
                }
            }
            Insert_nonFull(node->childrens[i], key);
        }
    }

    // 打印树结构
    void PrintBTree(node_t* node, int level) const
    {
        if (!node) 
        {
            return;
        }

        // 打印当前节点的键
        for (int i = 0; i < node->n; i++) 
        {
            std::cout << node->keys[i] << ' ';
        }
        std::cout << std::endl;

        // 递归打印当前节点的子节点
        if (!node->leaf) 
        {
            for (int i = 0; i < node->n + 1; i++) 
            {
                PrintBTree(node->childrens[i], level + 1);
            }
        }
    }
};