#include <iostream>
#include "printer.hpp"

void print_array(int *array, size_t length) {
    if (array == nullptr) {
        std::cout << "[null array";
        goto EndOfPrint;
    }
    std::cout << '[';
    if (length == 0)
        goto EndOfPrint;
    std::cout << array[0];
    for (size_t i = 1; i < length; ++i)
        std::cout << ", " << array[i];

    EndOfPrint:
    std::cout << ']' << std::endl;
}
