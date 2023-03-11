#include "intro_sort.hpp"

#include <algorithm>
#include <valarray>

// Function to perform insertion sort on subarray `a[low…high]`
static void insertion_sort(int a[], ssize_t low, ssize_t high)
{
    // start from the second element in the subarray
    // (the element at index `low` is already sorted)
    for (ssize_t i = low + 1; i <= high; i++)
    {
        int value = a[i];
        ssize_t j = i;

        // find index `j` within the sorted subset a[0…i-1]
        // where element a[i] belongs
        while (j > low && a[j - 1] > value)
        {
            a[j] = a[j - 1];
            j--;
        }

        // Note that the subarray `a[j…i-1]` is shifted to
        // the right by one position, i.e., `a[j+1…i]`

        a[j] = value;
    }
}

// Function to partition the array using Lomuto partition scheme
static ssize_t partition(int a[], ssize_t low, ssize_t high)
{
    // Pick the rightmost element as a pivot from the array
    int pivot = a[high];

    // elements less than the pivot will be pushed to the left of `p_index`
    // elements more than the pivot will be pushed to the right of `p_index`
    // equal elements can go either way
    ssize_t p_index = low;

    // each time we find an element less than or equal to the pivot, `p_index`
    // is incremented, and that element would be placed before the pivot.
    for (ssize_t i = low; i < high; i++)
    {
        if (a[i] <= pivot)
        {
            std::swap(a[i], a[p_index]);
            p_index++;
        }
    }

    // swap `p_index` with pivot
    std::swap(a[p_index], a[high]);

    // return `p_index` (index of the pivot element)
    return p_index;
}

// Quicksort randomized partition to rearrange elements across pivot
static ssize_t rand_partition(int a[], ssize_t low, ssize_t high)
{
    // choose a random index between `[low, high]`
    ssize_t pivot_index = rand() % (high - low + 1) + low;

    // swap the end element with the element present at a random index
    std::swap(a[pivot_index], a[high]);

    // call the partition procedure
    return partition(a, low, high);
}

// Function to perform heapsort on the given range of elements
static void heapsort(int* begin, int* end)
{
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}

// Function to perform intro_sort_ on the given array
static void intro_sort_(int a[], int* begin, int* end, int maxdepth)
{
    // perform insertion sort if partition size is 16 or smaller
    if ((end - begin) < 16)
    {
        insertion_sort(a, begin - a, end - a);
    }
    // perform heapsort if the maximum depth is 0
    else if (maxdepth == 0)
    {
        heapsort(begin, end + 1);
    }
    else
    {
        // otherwise, perform Quicksort
        ssize_t pivot = rand_partition(a, begin - a, end - a);
        intro_sort_(a, begin, a + pivot - 1, maxdepth - 1);
        intro_sort_(a, a + pivot + 1, end, maxdepth - 1);
    }
}

void intro_sort(int*& arr, size_t length)
{
    int max_depth = 2 * (int)std::log(length);
    intro_sort_(arr, arr, arr + length - 1, max_depth);
}
