/**
 * @brief 优先队列类型
 */
#include "..\p158 Heap_sort\Heap.h"

template <typename KeyType, typename ValueType>
class PQUEUE : public Heap<std::pair<KeyType, ValueType>>
{
public:
    using KeyValue = std::pair<KeyType, ValueType>;
    Heap<KeyValue> heap;

    explicit PQUEUE() {}
    virtual ~PQUEUE() {}

    // 返回优先队列中具有最大键字的元素
    KeyValue Maximum() const
    {
        if (heap.heapSize == 0)
        {
            throw std::runtime_error("Priority queue is empty!");
        }
        return heap.heapArray[0];
    }

    // 去掉并返回优先队列中具有最大键字的元素
    KeyValue Extract_Max()
    {
        if (heap.heapSize <= 0)
        {
            throw std::runtime_error("Priority queue is empty, cannot extract maximum!");
        }

        KeyValue max = heap.heapArray[0];
        heap.heapArray[0] = heap.heapArray[heap.heapSize - 1];
        --heap.heapSize;
        heap.Heapify(0);
        return max;
    }

    // 将下标 i 的关键字值增加到 newKey
    void Increase_Key(int i, const KeyType &newKey)
    {
        if (newKey < heap.heapArray[i].first)
        {
            throw std::runtime_error("New key is smaller than current key!");
        }
        heap.heapArray[i].first = newKey;
        while (i > 0 && heap.heapArray[heap.Parent(i)].first < heap.heapArray[i].first)
        {
            std::swap(heap.heapArray[heap.Parent(i)], heap.heapArray[i]); // 与父节点交换
            i = heap.Parent(i);
        }
    }

    // 将键值对插入优先队列中
    void Insert(const KeyType &key, const ValueType &value)
    {
        ++heap.heapSize;
        heap.heapArray.emplace_back(std::make_pair(std::numeric_limits<KeyType>::min(), value));
        Increase_Key(heap.heapSize - 1, key);
    }
};