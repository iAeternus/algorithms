#include <iostream>
#include <vector>

#include "YoungMatrix.h"

int main() 
{
    YoungMatrix youngMatrix(5, 5);
    youngMatrix.Print();

    youngMatrix.Insert(10);
    youngMatrix.Print();
    youngMatrix.Insert(7);
    youngMatrix.Print();
    youngMatrix.Insert(5);
    youngMatrix.Print();
    youngMatrix.Insert(3);
    youngMatrix.Print();
    youngMatrix.Insert(12);
    youngMatrix.Print();
    youngMatrix.Insert(8);
    youngMatrix.Print();
    youngMatrix.Insert(6);
    youngMatrix.Print();
    youngMatrix.Insert(1);
    youngMatrix.Print();

    std::cout << "Search 12: " << (youngMatrix.Search(12) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 4: " << (youngMatrix.Search(4) ? "Found" : "Not found") << std::endl;

    youngMatrix.Print();
    int min_value = youngMatrix.Extract_min();
    std::cout << "Extracted min value: " << min_value << std::endl;

    youngMatrix.Print();

    return 0;
}