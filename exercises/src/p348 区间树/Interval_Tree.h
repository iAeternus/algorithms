/**
 * @brief 区间树
 * @brief 通过扩张红黑树得到的由区间构成的动态集合
 * @author Ricky
 * @date 2023/7/30
 * @version 1.0
*/
#pragma once

const std::string RED_COLOR_CODE = "\033[1;31m";  // 设置文本颜色为红色的ANSI转义码
const std::string DEFAULT_COLOR_CODE = "\033[0m"; // 恢复默认文本颜色的ANSI转义码

// 区间对象定义
template<typename dataType>
class Interval
{
public:
    Interval (const dataType& low = 0, const dataType& high = 0) : low (low), high (high) {}
    Interval (const Interval& other) : low (other.low), high (other.high) {}

    // getter
    dataType Low () const { return low; }
    dataType High () const { return high; }

    // 判断两区间是否重叠
    bool isOverlap (const Interval& other) const
    {
        return low <= other.high && other.low <= high;
    }

    friend bool operator<(const Interval& left, const Interval& right)
    {
        return left.low < right.low;
    }

    friend bool operator>(const Interval& left, const Interval& right)
    {
        return left.low > right.low;
    }

    // 区间相等
    friend bool operator==(const Interval& left, const Interval& right)
    {
        return left.low == right.low && left.high == right.high;
    }

    // 区间不等
    friend bool operator!=(const Interval& left, const Interval& right)
    {
        return left.high != right.high || left.low != right.low;
    }

    friend std::istream& operator>>(std::istream& in, Interval& interval)
    {
        in >> interval.low >> interval.high;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Interval& interval)
    {
        out << '[' << interval.low << ", " << interval.high << ']';
        return out;
    }
protected:
    dataType low; // 低端点
    dataType high; // 高端点
};

// 区间树，与红黑树类似
template <typename dataType>
class IntTree
{
public:
    // 颜色相关变量定义
    using Color = bool;
    const static bool RED = true;    // 红
    const static bool BLACK = false; // 黑

    // 树节点定义
    struct stNode
    {
        Interval<dataType> interval;  // 区间，充当键
        int max;        // 子树中区间端点的最大值
        Color color;    // 颜色
        stNode* left;   // 左孩子
        stNode* right;  // 右孩子
        stNode* parent; // 父亲

        stNode (const Interval<dataType>& interval, int max = 0, Color color = RED,
            stNode* const left = nullptr, stNode* const right = nullptr, stNode* const parent = nullptr)
            : interval (interval), max (max), color (color), left (left), right (right), parent (parent)
        {}
        stNode (Interval<dataType>&& interval, int&& max, Color color = RED)
            : interval (std::move (interval)), max (std::move (max)), color (color), left (nullptr), right (nullptr), parent (nullptr)
        {}
        stNode (const stNode& other)
            : interval (other.interval), max (other.max), color (other.color), parent (other.parent), left (other.left), right (other.right)
        {}

        friend std::ostream& operator<<(std::ostream& out, const stNode& node)
        {
            out << '(' << node.interval << ' ' << node.max << ')';
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

        Interval<dataType>& operator*() const { return current->interval; }
        Interval<dataType>* operator->() const { return &current->interval; }

        friend std::ostream& operator<<(std::ostream& out, const stIterator& iterator)
        {
            out << '(' << iterator.current->interval << ' ' << iterator.current->max << ')';
            return out;
        }
    private:
        node_t* current; // 迭代器当前位置
    };
    using iterator = stIterator;

protected:
    node_t* root; // 根节点
    int size;     // 节点个数
    // 哨兵：所有叶结点的孩子且是根节点的父亲
    inline static node_t* nil = new node_t (Interval<dataType> (), -1, BLACK);

public:
    // 实际暴露出来的公有函数
    IntTree () : root (nil), size (0)
    {
        nil->left = nil->right = root;
    }

    virtual ~IntTree ()
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
     * @param interval 区间
     * @return 找到返回数据迭代器，否则返回end()
     */
    iterator Find (const Interval<dataType>& interval) const
    {
        node_t* cur = root;
        while (cur != nil && cur->interval != interval)
        {
            if (interval < cur->interval)
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
     * @param interval
     */
    bool Has (const Interval<dataType>& interval) const
    {
        node_t* cur = root;
        while (cur != nil && cur->interval != interval)
        {
            if (interval < cur->interval)
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
     * @param interval
     * @return 键存在返回键所对应的值，否则返回随机值
     */
    Interval<dataType>& operator[](const Interval<dataType>& interval) const
    {
        node_t* cur = root;
        while (cur != nil && cur->interval != interval)
        {
            if (interval < cur->interval)
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

        return cur->interval;
    }

    /**
     * @brief 插入节点
     * @param interval 插入节点的区间
     * @return 成功操作返回 true，否则返回 false
     */
    bool Insert (const Interval<dataType>& interval)
    {
        bool ret = true;
        node_t* prev = nil;
        node_t* cur = root;
        node_t* newNode = new node_t (interval);
        while (cur != nil)
        {
            prev = cur;
            if (newNode->interval < cur->interval)
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
        else if (newNode->interval < prev->interval)
        {
            prev->left = newNode;
        }
        else
        {
            prev->right = newNode;
        }
        newNode->left = newNode->right = nil;
        ++size;
        UpdateMax (newNode);  // 更新插入节点的max值
        Insert_Fixup (newNode);
        return ret;
    }

    /**
     * @brief 删除节点
     * @param interval 删除节点的区间
     */
    void Delete (const Interval<dataType>& interval)
    {
        iterator it = Find (interval);
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
        UpdateMax (x); // 更新替代的节点的 max 值
        if (y_original_color == BLACK) // 如果是黑色，说明删除或移动 y 引起了红黑性质的破坏
        {
            Delete_Fixup (x); // 调整
        }
    }

    /**
     * @brief 查找与目标区间重叠的区间
     * @param i 目标区间
     * @return 返回树中与 i 重叠的区间，若不存在返回 nil
    */
    node_t* Search (const Interval<dataType>& i) const
    {
        node_t* x = root;
        while (x != nil && !i.isOverlap (x->interval))
        {
            if (x->left != nil && x->left->max >= i.Low ())
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

    /**
     * @brief 打印树的结构
     */
    void PrintTree () const
    {
        PrintTree (root, 0);
    }

protected:
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
            std::cout << x->interval << ' ';
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
            std::cout << x->interval << ' ';
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
            std::cout << x->interval << ' ';
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
    }

    // 更新 node 的 max 值
    void UpdateMax (node_t* node)
    {
        if (node == nil) return;

        node->max = node->interval.High ();
        if (node->left != nil)
        {
            node->max = std::max (node->max, node->left->max);
        }
        if (node->right != nil)
        {
            node->max = std::max (node->max, node->right->max);
        }
        UpdateMax (node->parent);  // 向上更新max值
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
        UpdateMax (root);
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
        UpdateMax (root);
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
};
