#include <iostream>
#include <vector>

std::vector<bool> binary_add(const std::vector<bool>& bin_left, const std::vector<bool>& bin_right)
{
    std::vector<bool> bin_res(bin_left.size() + 1, false);

    bool carry = false; // 是否进位

    for (int i = bin_left.size() - 1; i >= 0; i--)
    {
        bool bit_left = bin_left[i];
        bool bit_right = bin_right[i];

        bool sum = bit_left ^ bit_right ^ carry; // 通过异或进行二进制运算
        carry = (bit_left && bit_right) || (bit_left && carry) || (bit_right && carry);

        bin_res[i + 1] = sum;
    }

    bin_res[0] = carry;

    return bin_res;
}

void print_binary(const std::vector<bool>& binary)
{
    for (const bool bit : binary)
    {
        std::cout << bit;
    }
    std::cout << std::endl;
}

std::vector<bool> read_binary()
{
    std::vector<bool> binary;
    std::string input;
    std::cout << "Enter a binary number: ";
    std::cin >> input;

    for (char bit : input)
    {
        binary.push_back(bit == '1');
    }

    return binary;
}

int main()
{
    std::vector<bool> bin_left = read_binary();
    std::vector<bool> bin_right = read_binary();

    std::cout << "  ";
    print_binary(bin_left);

    std::cout << "+ ";
    print_binary(bin_right);

    std::vector<bool> bin_res = binary_add(bin_left, bin_right);

    std::cout << " ";
    print_binary(bin_res);

    return 0;
}