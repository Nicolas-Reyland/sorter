#include "merge_sort.hpp"

#include <cstring>

void merge(int arr[], size_t left, size_t mid, size_t right)
{
    size_t sub_arr_left = mid - left + 1;
    size_t sub_arr_right = right - mid;

    // Create temp arrays
    int* left_arr = new int[sub_arr_left];
    int* right_arr = new int[sub_arr_right];

    // Copy data to temp arrays left_arr[] and right_arr[]
    memcpy(left_arr, arr + left, sub_arr_left * sizeof(int));
    memcpy(right_arr, arr + mid + 1, sub_arr_right * sizeof(int));

    size_t left_sub_arr_index = 0, right_sub_arr_index = 0;
    size_t write_index = left;

    // Merge the temp arrays back into arr[left..right]
    while (left_sub_arr_index < sub_arr_left
           && right_sub_arr_index < sub_arr_right)
    {
        if (left_arr[left_sub_arr_index] <= right_arr[right_sub_arr_index])
        {
            arr[write_index] = left_arr[left_sub_arr_index++];
        }
        else
        {
            arr[write_index] = right_arr[right_sub_arr_index++];
        }
        write_index++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (left_sub_arr_index < sub_arr_left)
        arr[write_index++] = left_arr[left_sub_arr_index++];

    // Copy the remaining elements of
    // right[], if there are any
    while (right_sub_arr_index < sub_arr_right)
        arr[write_index++] = right_arr[right_sub_arr_index++];

    delete[] left_arr;
    delete[] right_arr;
}

static void merge_sort_(int array[], size_t begin, size_t end);

void merge_sort(int*& arr, size_t length)
{
    merge_sort_(arr, 0, length - 1);
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void merge_sort_(int array[], size_t begin, size_t end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    merge_sort_(array, begin, mid);
    merge_sort_(array, mid + 1, end);
    merge(array, begin, mid, end);
}