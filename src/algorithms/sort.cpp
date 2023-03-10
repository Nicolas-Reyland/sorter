#include "sort.hpp"

bool is_sorted(const int *arr, size_t length) {
    for (size_t i = 1; i < length; ++i)
        if (arr[i - 1] > arr[i])
            return false;

    return true;
}
