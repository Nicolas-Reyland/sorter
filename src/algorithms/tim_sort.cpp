#include "tim_sort.hpp"

// C++ program to perform TimSort.
#include<bits/stdc++.h>

const size_t RUN = 32;

// This function sorts array from left index
// to right index which is of size atmost RUN
static void insertion_sort(int arr[], size_t left, size_t right)
{
    for (size_t i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        size_t j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

// Merge function merges the sorted runs
static void merge(int*& arr, size_t l, size_t m, size_t r)
{

    // Original array is broken in two parts
    // left and right array
    size_t len1 = m - l + 1, len2 = r - m;
    int* left = new int[len1];
    int* right = new int[len2];
    memcpy(left, arr + l, len1 * sizeof(int));
    memcpy(right, arr + m + 1, len2 * sizeof(int));

    size_t i = 0;
    size_t j = 0;
    size_t k = l;

    // After comparing, we
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left, if any
    while (i < len1)
        arr[k++] = left[i++];

    // Copy remaining element of right, if any
    while (j < len2)
        arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
void tim_sort(int *& arr, size_t n)
{

    // Sort individual subarrays of size RUN
    for (size_t i = 0; i < n; i+=RUN)
        insertion_sort(arr, i, std::min<size_t>((i + RUN - 1), (n - 1)));

    // Start merging from size RUN (or 32).
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    for (size_t size = RUN; size < n;
         size = 2*size)
    {

        // pick starting point of
        // left sub array. We
        // are going to merge
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we
        // increase left by 2*size
        for (size_t left = 0; left < n;
             left += 2*size)
        {

            // find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            size_t mid = left + size - 1;
            size_t right = std::min<size_t>((left + 2*size - 1), (n-1));

            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if(mid < right)
                merge(arr, left, mid, right);
        }
    }
}
