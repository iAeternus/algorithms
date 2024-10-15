/**
 * @brief 顺序统计树
 * @brief 节点具有大小属性的红黑树，可用于顺序统计和秩，比快速选择快，时间复杂度 O(logn)
 * @author Ricky
 * @date 2023/7/30
 * @version 1.0
 */
#pragma once

const std::string RED_COLOR_CODE = "\033[1;31m";  // 设置文本颜色为红色的ANSI转义码
const std::string DEFAULT_COLOR_CODE = "\033[0m"; // 恢复默认文本颜色的ANSI转义码

// 顺序统计树，与红黑树类似，只是节点类新增了 count 属性
template <typename keyType, typename dataType>
class OSTree
{
public:
    // 颜色相关变量定义
    using Color = bool;
    const static bool RED = true;    // 红
    const static bool BLACK = false; // 黑

    // 树节点定义
    struct stNode
    {
        keyType key;    // 键
        dataType data;  // 值
        Color color;    // 颜色
        int count;      // 以 node 为根的子树（包括 node）的节点数
        stNode* left;   // 左孩子
        stNode* right;  // 右孩子
        stNode* parent; // 父亲

        stNode (const keyType& key, const dataType& data, Color color = RED, int count = 0,
            stNode* const left = nullptr, stNode* const right = nullptr, stNode* const parent = nullptr)
            : key (key), data (data), color (color), count (count), left (left), right (right), parent (parent)
        {}
        stNode (keyType&& key, dataType&& data, Color color = RED)
            : key (std::move (key)), data (std::move (data)), color (color), count (0), left (nullptr), right (nullptr), parent (nullptr)
        {}
        stNode (const stNode& other)
            : key (other.key), data (other.data), color (other.color), count (other.count), parent (other.parent), left (other.left), right (other.right)
        {}

        friend std::ostream& operator<<(std::ostream& out, const stNode& node)
        {
            const stNode* const p = &node;
            if (p)
            {
                out << '(' << node.key << ' ' << node.data << ')';
            }
            else
            {
                out << "null";
            }
            return out;
        }
    };
    using node_t = stNode;

    // 迭代器类型定义，采用中序遍历迭代
    class stIterator
    {
    public:
        stIterator (node_t* const current = nullptr) : current (current) {}

        node_t* Current () const { return current; }

        stIterator& operator++()
        {
            current = Successor (current);
            return *this;
        }

        stIterator operator++(int)
        {
            stIterator temp = *this;
            ++(*this);
            return temp;
        }

        stIterator& operator--()
        {
            current = Precursor (current);
            return *this;
        }

        stIterator operator--(int)
        {
            stIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const stIterator& other) const { return current == other.current; }
        bool operator!=(const stIterator& other) const { return current != other.current; }

        dataType& operator*() const { return current->data; }
        dataType* operator->() const { return &current->data; }

        friend std::ostream& operator<<(std::ostream& out, const stIterator& iterator)
        {
            out << '(' << iterator.current->key << ' ' << iterator.current->data << ')';
            return out;
        }

    private:
        node_t* current; // 迭代器当前位置
    };
    using iterator = stIterator;

private:
    node_t* root; // 根节点
    int size;     // 节点个数
    // 哨兵：所有叶结点的孩子且是根节点的父亲
    inline static node_t* nil = new node_t (-1, -1, BLACK);

public:
    // 实际暴露出来的公有函数
    OSTree () : root (nil), size (0)
    {
        nil->left = nil->right = root;
    }

    ~OSTree ()
    {
        Clear ();
        delete nil;
        root = nil = nullptr;
    }

    /**
     * @brief 清空红黑树，使之恢复空树状态
     */
    void Clear ()
    {
        if (!Empty ())
        {
            Release (root);
            root = nil;
            size = 0;
        }
    }

    iterator begin ()
    {
        if (!root)
        {
            return iterator (nil);
        }
        return iterator (Minimum (root));
    }

    iterator end ()
    {
        return iterator (nil);
    }

    /**
     * @brief 取最小值
     */
    iterator Minimum () const
    {
        return iterator (Minimum (root));
    }

    /**
     * @brief 取最大值
     */
    iterator Maximum () const
    {
        return iterator (Maximum (root));
    }

    /**
     * @brief 获取节点个数
     */
    int Size () const { return size; }

    /**
     * @brief 判断树是否为空
     */
    bool Empty () const { return root == nullptr; }

    /**
     * @brief 遍历打印整棵树
     */
    void Preorder () const
    {
        Preorder (root);
        std::cout << '\n';
    }
    void InOrder () const
    {
        InOrder (root);
        std::cout << '\n';
    }
    void Postorder () const
    {
        Postorder (root);
        std::cout << '\n';
    }

    /**
     * @brief 查找数据
     * @param key 数据键名称
     * @return 找到返回数据迭代器，否则返回end()
     */
    iterator Find (const keyType& key)
    {
        node_t* cur = root;
        while (cur != nil && cur->key != key)
        {
            if (key < cur->key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        return iterator (cur);
    }

    /**
     * @brief 判断数据是否存在
     * @param key
     */
    bool Has (const keyType& key)
    {
        node_t* cur = root;
        while (cur != nil && cur->key != key)
        {
            if (key < cur->key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        return cur != nil;
    }

    /**
     * @brief 取数据内容，重载了下标运算符，方便获取数据
     * @param key
     * @return 键存在返回键所对应的值，否则返回随机值
     */
    dataType& operator[](const keyType& key)
    {
        node_t* cur = root;
        while (cur != nil && cur->key != key)
        {
            if (key < cur->key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        if (cur == nil) // 没找到
        {
            return {};
        }

        return cur->data;
    }

    /**
     * @brief 插入节点
     * @param key 插入节点的键
     * @param data 插入节点的值
     * @return 成功操作返回 true，否则返回 false
     */
    bool Insert (const keyType& key, const dataType& data)
    {
        bool ret = true;
        node_t* prev = nil;
        node_t* cur = root;
        node_t* newNode = new node_t (key, data, RED);
        while (cur != nil)
        {
            prev = cur;
            if (newNode->key < cur->key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        newNode->parent = prev;
        if (prev == nil)
        {
            root = newNode;
        }
        else if (newNode->key < prev->key)
        {
            prev->left = newNode;
        }
        else
        {
            prev->right = newNode;
        }
        newNode->left = newNode->right = nil;
        ++size;
        Insert_Fixup (newNode);
        return ret;
    }

    /**
     * @brief 删除节点
     * @param key 删除节点的键
     */
    void Delete (const keyType& key)
    {
        iterator it = Find (key);
        if (it == end ())
        {
            return;
        }

        node_t* z = it.Current (); // z 要删的节点
        node_t* y = z;            // 代替 z 的节点
        node_t* x = nil;          // 指向 y 的原始位置，用 y 的原右孩子 x 代替 y
        Color y_original_color = y->color;

        if (z->left == nil) // z 的左子树空
        {
            x = z->right;
            Transplant (z, z->right);
        }
        else if (z->right == nil) // z 的右子树空
        {
            x = z->left;
            Transplant (z, z->left);
        }
        else // z 左右孩子双全
        {
            y = Minimum (z->right);       // 查找 z 的后继
            y_original_color = y->color; // 记住 y 的颜色
            x = y->right;                // x 指向 y 的右子树
            if (y->parent == z)          // 如果后继 y 就是 z 的孩子，说明 y 没有孩子，可以直接替换
            {
                x->parent = y;
            }
            else // 如果 y 在下面
            {
                Transplant (y, y->right); // 删除节点 y
                y->right = z->right;     // y 继承 z 的右子树
                y->right->parent = y;
            }
            Transplant (z, y);  // 用 y 替换 z
            y->left = z->left; // y 继承 z 的左子树
            y->left->parent = y;
            y->color = z->color; // y 继承 z 的颜色
        }

        --size;
        if (y_original_color == BLACK) // 如果是黑色，说明删除或移动 y 引起了红黑性质的破坏
        {
            Delete_Fixup (x); // 调整
        }
    }

    /**
     * @brief 顺序统计树功能函数：顺序选择
     * @param i 树中的第 i 小关键字（从 1 开始）
     * @return 返回包含第 i 小关键字的节点指针，树空或 i 非法返回 nil
    */
    node_t* Select (int i) const
    {
        if (root && i > 0 && i <= size)
        {
            return Select (root, i);
        }
        return nil;
    }

    /**
     * @brief 顺序统计树功能函数：确定一个元素的秩
     * @brief 秩：中序遍历次数排在目标节点之前的节点数加 1（代表目标节点自身）
     * @param key 要计算的节点的键
     * @return key 键字对应的节点的秩，key 不存在返回随机值
    */
    int Rank (const keyType& key)
    {
        iterator it = Find (key);
        if (it == end ())
        {
            return {};
        }

        node_t* x = it.Current ();
        int rank = x->left->count + 1;
        node_t* y = x;
        while (y != root)
        {
            if (y == y->parent->right)
            {
                rank += y->parent->left->count + 1;
            }
            y = y->parent;
        }
        return rank;
    }

    /**
     * @brief 获取集合中的下中位数节点
    */
    node_t* Median () const
    {
        return Select (static_cast<int>(size / 2));
    }

    /**
     * @brief 打印树的结构
     */
    void PrintTree () const
    {
        PrintTree (root, 0);
    }

private:
    // 查询以 node 为根节点的树的最小元
    static node_t* Minimum (node_t* node)
    {
        if (!node)
            return nullptr;
        while (node != nil && node->left != nil)
        {
            node = node->left;
        }
        return node;
    }

    // 查询以 node 为根节点的树的最大元
    static node_t* Maximum (node_t* node)
    {
        if (!node)
            return nullptr;
        while (node != nil && node->right != nil)
        {
            node = node->right;
        }
        return node;
    }

    // 返回 node 的后继
    static node_t* Successor (node_t* node)
    {
        if (!node)
            return nullptr;
        // 节点右子树非空，后继为右子树中的最左节点（最小节点）
        if (node->right != nil)
        {
            return Minimum (node->right);
        }
        // 右子树为空时，找到第一个拥有左子节点的祖先节点
        node_t* successor = node->parent;
        while (successor != nil && node == successor->right)
        {
            node = successor;
            successor = successor->parent;
        }
        return successor;
    }

    // 返回 node 的前驱
    static node_t* Precursor (node_t* node)
    {
        if (!node)
            return nullptr;
        // 如果节点的左子树非空，前驱是左子树的最右节点（最大节点）
        if (node->left != nil)
        {
            return Maximum (node->left);
        }
        // 左子树为空时，找到第一个拥有右子节点的祖先节点
        node_t* precursor = node->parent;
        while (precursor != nil && node == precursor->left)
        {
            node = precursor;
            precursor = precursor->parent;
        }
        return precursor;
    }

    // 释放节点内存
    void Release (node_t* node)
    {
        if (node != nil)
        {
            if (node->left != nil)
            {
                Release (node->left);
            }
            if (node->right != nil)
            {
                Release (node->right);
            }
            delete node;
        }
    }

    // 前序遍历以 x 为根节点的子树
    void Preorder (node_t* const x) const
    {
        if (x != nil)
        {
            std::cout << x->data << ' ';
            Preorder (x->left);
            Preorder (x->right);
        }
    }

    // 中序遍历以 x 为根节点的子树
    void InOrder (node_t* const x) const
    {
        if (x != nil)
        {
            InOrder (x->left);
            std::cout << x->data << ' ';
            InOrder (x->right);
        }
    }

    // 后序遍历以 x 为根节点的子树
    void Postorder (node_t* const x) const
    {
        if (x != nil)
        {
            Postorder (x->left);
            Postorder (x->right);
            std::cout << x->data << ' ';
        }
    }

    // 左旋
    void Left_Rotate (node_t* node)
    {
        node_t* y = node->right; // set y
        node->right = y->left;   // 让 y 的左子树变成 node 的右子树
        if (y->left != nil)
        {
            y->left->parent = node;
        }
        y->parent = node->parent; // y 链接 node 的父亲
        if (node->parent == nil)  // 空树
        {
            root = y;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = y;
        }
        else
        {
            node->parent->right = y;
        }
        y->left = node; // node 成为 y 的左子树
        node->parent = y;
        // 维护 count
        y->count = node->count;
        node->count = node->left->count + node->right->count + 1;
    }

    // 右旋
    void Right_Rotate (node_t* node)
    {
        node_t* y = node->right; // set y
        node->left = y->right;   // 让 y 的右子树变成 node 的左子树
        if (y->right != nil)
        {
            y->right->parent = node;
        }
        y->parent = node->parent; // y 链接 node 的父亲
        if (node->parent == nil)  // 空树
        {
            root = y;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = y;
        }
        else
        {
            node->parent->right = y;
        }
        y->right = node; // node 成为 y 的右子树
        node->parent = y;
        // 维护 count
        y->count = node->count;
        node->count = node->left->count + node->right->count + 1;
    }

    /**
     * @brief 插入后的调整操作
     * @brief Case 1: 当叔节点是红色时，将父节点和叔节点变为黑色，祖父节点变为红色，并将当前节点上移两层
     * @brief Case 2: 当叔节点是黑色且当前节点是父节点的右孩子时，通过左旋将当前节点转换为 Case 3
     * @brief Case 3: 当叔节点是黑色且当前节点是父节点的左孩子时，将父节点变为黑色，祖父节点变为红色，并通过右旋恢复平衡
     */
    void Insert_Fixup (node_t* node)
    {
        while (node->parent->color == RED)
        {
            if (node->parent == node->parent->parent->left)
            {
                node_t* y = node->parent->parent->right;
                if (y->color == RED) // case 1: 叔节点是红色
                {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED; // 更改父节点和叔节点的颜色
                    node = node->parent->parent;       // 向上移两层继续修正
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent; // case 2: 叔节点是黑色，且当前节点是父节点的右孩子
                        Left_Rotate (node);   // 左旋，转为case 3
                    }

                    node->parent->color = BLACK; // case 3: 叔节点是黑色，且当前节点是父节点的左孩子
                    node->parent->parent->color = RED;
                    Right_Rotate (node->parent->parent); // 右旋
                }
            }
            else // 父节点为祖父节点的右孩子的情况（对称情况）
            {
                node_t* y = node->parent->parent->left;
                if (y->color == RED) // case 1: 叔节点是红色
                {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED; // 更改父节点和叔节点的颜色
                    node = node->parent->parent;       // 向上移两层继续修正
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent; // case 2: 叔节点是黑色，且当前节点是父节点的左孩子
                        Right_Rotate (node);  // 右旋，转为case 3
                    }

                    node->parent->color = BLACK; // case 3: 叔节点是黑色，且当前节点是父节点的右孩子
                    node->parent->parent->color = RED;
                    Left_Rotate (node->parent->parent); // 左旋
                }
            }
        }
        root->color = BLACK; // 最后设置根节点为黑色
    }

    // 用一棵以 v 为根的子树替换以 u 为根的子树，并成为后者父亲的孩子结点
    void Transplant (node_t* u, node_t* v)
    {
        if (u->parent == nil)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // 删除后的调整操作
    void Delete_Fixup (node_t* x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                node_t* w = x->parent->right;

                // Case 1: 兄弟节点是红色
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    Left_Rotate (x->parent);
                    w = x->parent->right;
                }

                // Case 2: 兄弟节点是黑色，且兄弟节点的两个子节点都是黑色
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    // Case 3: 兄弟节点是黑色，兄弟节点的右子节点是黑色，左子节点是红色
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        Right_Rotate (w);
                        w = x->parent->right;
                    }

                    // Case 4: 兄弟节点是黑色，兄弟节点的右子节点是红色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    Left_Rotate (x->parent);
                    x = root;
                }
            }
            else // 镜像对称的情况，与上述代码类似，只需要交换left和right
            {
                node_t* w = x->parent->left;

                // Case 1: 兄弟节点是红色
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    Right_Rotate (x->parent);
                    w = x->parent->left;
                }

                // Case 2: 兄弟节点是黑色，且兄弟节点的两个子节点都是黑色
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    // Case 3: 兄弟节点是黑色，兄弟节点的左子节点是黑色，右子节点是红色
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        Left_Rotate (w);
                        w = x->parent->left;
                    }

                    // Case 4: 兄弟节点是黑色，兄弟节点的左子节点是红色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    Right_Rotate (x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // 打印以 node 为根节点的子树结构
    void PrintTree (node_t* const node, size_t level) const
    {
        if (node != nil)
        {
            PrintTree (node->right, level + 1);
            for (size_t i = 0; i < level; i++)
            {
                std::cout << "          ";
            }
            if (node->color == RED)
            {
                std::cout << RED_COLOR_CODE << *node << DEFAULT_COLOR_CODE << std::endl;
            }
            else if (node->color == BLACK)
            {
                std::cout << *node << std::endl;
            }
            PrintTree (node->left, level + 1);
        }
    }

    // 顺序选择，返回以 node 为根的子树中包含第 i 小关键字的节点指针
    node_t* Select (node_t* node, int i) const
    {
        int rank = node->left->count + 1; // node 的秩
        if (i == rank)
        {
            return node;
        }
        else if (i < rank)
        {
            return Select (node->left, i);
        }
        else
        {
            return Select (node->right, i - rank);
        }
    }
};
