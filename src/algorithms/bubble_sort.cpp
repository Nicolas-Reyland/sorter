#include "bubble_sort.hpp"

#include <algorithm>

void bubble_sort(int*& arr, size_t length)
{
    for (size_t i = 0; i < length - 1; i++)
        for (size_t j = 0; j < length - i - 1; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}
