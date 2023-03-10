#pragma once

#include <cstddef>
#include <cstdlib>

typedef void (sort_function(int *&, size_t));

bool is_sorted(const int *arr, size_t length);