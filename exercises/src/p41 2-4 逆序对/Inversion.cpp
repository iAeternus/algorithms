#include <iostream>
#include <vector>

template<typename T>
int MergeCount(std::vector<T>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int S3 = 0;
    std::vector<T> leftArr(n1), rightArr(n2);
    int i, j;
    for (i = 0; i < n1; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        rightArr[j] = arr[mid + j + 1];
    }
    i = j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k++] = leftArr[i++];
        }
        else // 逆序对
        {
            arr[k++] = rightArr[j++];
            S3 += mid - left - i + 1; // 剩余未处理的左子数组元素数量 + 1
        }
    }
    while (i < n1)
    {
        arr[k++] = leftArr[i++];
    }
    while (j < n2)
    {
        arr[k++] = rightArr[j++];
    }
    return S3;
}

template<typename T>
int CountInver(std::vector<T>& arr, int left, int right)
{
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    int S1 = CountInver(arr, left, mid); // 左边的逆序对
    int S2 = CountInver(arr, mid + 1, right); // 右边的逆序对
    int S3 = MergeCount(arr, left, mid, right); // 跨越 mid 的逆序对
    return S1 + S2 + S3;
}

template<typename T>
int CountInver(std::vector<T>& arr)
{
    return CountInver(arr, 0, arr.size() - 1);
}

int main()
{
    std::vector<int> arr = {13, 8, 10, 6, 15, 18, 12, 20, 9, 14, 17, 19};
    std::cout << "The number of pairs in reverse order = " << CountInver(arr) << std::endl;
    return 0;
}