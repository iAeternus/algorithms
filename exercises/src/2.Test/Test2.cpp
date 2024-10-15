#include <iostream>
#include <vector>
#include <unordered_set>

void FindUniqueElements(const std::vector<int>& arr) {
    std::unordered_set<int> unique_elements;

    for (int num : arr) {
        if (unique_elements.find(num) == unique_elements.end()) {
            // 如果元素不在集合中，添加到集合中
            unique_elements.insert(num);
        } else {
            // 如果元素已经在集合中，从集合中移除
            unique_elements.erase(num);
        }
    }

    std::cout << "Unique elements: ";
    for (int unique_element : unique_elements) {
        std::cout << unique_element << " ";
    }
    std::cout << std::endl;
}

int main() {
    // std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     std::vector<int> arr = {2, 4, 7, 9, 4, 7, 2, 11, 9, 15};
    FindUniqueElements(arr);
    return 0;
}
