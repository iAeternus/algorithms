#include <iostream>
#include <vector>

template<typename T>
int Linear_lookup(std::vector<T>& arr, const T& target)
{
    int index = -1;
    for(size_t i = 0; i < arr.size(); i++)
    {
        if(arr[i] == target)
        {
            index = i;
            break;
        }
    }
    return index;
}

int main()
{
    std::vector<int> arr = {3, 2, 4, 1, 5};
    std::cout << "arr[" << Linear_lookup(arr, 4) << "] = " << 4 << std::endl;
    return 0;
}