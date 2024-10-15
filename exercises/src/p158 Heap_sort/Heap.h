/**
 * 堆工具类型，可自定义最大堆和最小堆，默认为最大堆
*/

// 比较函数对象
struct greater // 最大堆 -> 升序排序
{
    template<typename T>
    bool operator()(const T& a, const T& b) const
    {
        return a > b;
    }
};

struct less // 最小堆 -> 降序排序
{
    template<typename T>
    bool operator()(const T& a, const T& b) const
    {
        return a < b;
    }
};

template<typename ValueType, typename Compare = greater>
class Heap
{
public:
    std::vector<ValueType> heapArray;
    int heapSize;
    Compare compareFn;

    explicit Heap() : heapSize(0) {}
    virtual ~Heap() {}

    static int Parent(int i) { return i >> 1; }
    static int Left(int i) { return (i << 1) + 1; }
    static int Right(int i) { return (i << 1) + 2; }

    void Heapify(int i)
    {
        int largest = i;
        int left = Left(i);
        int right = Right(i);
        

        if (left < heapSize && compareFn(heapArray[left], heapArray[largest]))
        {
            largest = left;
        }
        if (right < heapSize && compareFn(heapArray[right], heapArray[largest]))
        {
            largest = right;
        }

        if (largest != i)
        {
            std::swap(heapArray[i], heapArray[largest]);
            Heapify(largest);
        }
    }

    void BuildHeap(std::vector<ValueType>& arr)
    {
        heapArray = std::move(arr);
        heapSize = heapArray.size();
        for (int i = (heapSize / 2) - 1; i >= 0; --i)
        {
            Heapify(i);
        }
    }

    void HeapSort(std::vector<ValueType>& arr)
    {
        BuildHeap(arr);
        for (int i = heapSize - 1; i > 0; --i)
        {
            std::swap(heapArray[0], heapArray[i]);
            --heapSize;
            Heapify(0);
        }
        arr = std::move(heapArray);
    }
};
