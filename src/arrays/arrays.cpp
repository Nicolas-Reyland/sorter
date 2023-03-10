#include <cstdlib>
#include "arrays.hpp"
#include "sort.hpp"

int *random_array(size_t length) {
    int *arr = new int[length];
    for (size_t i = 0; i < length; ++i)
        arr[i] = std::rand();
    return arr;
}

int *random_array(size_t length, int max_val) {
    int *arr = new int[length];
    for (size_t i = 0; i < length; ++i)
        arr[i] = std::rand() % max_val;
    return arr;
}

