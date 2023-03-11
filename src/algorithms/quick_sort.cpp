#include "quick_sort.hpp"

#include <algorithm>

static int partition(int arr[], ssize_t start, ssize_t end)
{
    int pivot = arr[start];

    ssize_t count = 0;
    for (ssize_t i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    ssize_t pivot_index = start + count;
    std::swap(arr[pivot_index], arr[start]);

    // Sorting left and right parts of the pivot element
    ssize_t i = start, j = end;

    while (i < pivot_index && j > pivot_index)
    {
        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivot_index && j > pivot_index)
        {
            std::swap(arr[i++], arr[j--]);
        }
    }

    return pivot_index;
}

static void quick_sort_(int arr[], ssize_t start, ssize_t end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quick_sort_(arr, start, p - 1);

    // Sorting the right part
    quick_sort_(arr, p + 1, end);
}

void quick_sort(int*& arr, size_t length)
{
    quick_sort_(arr, 0, length - 1);
}
