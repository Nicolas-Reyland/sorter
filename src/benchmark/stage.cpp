#include "stage.hpp"
#include <string>
#include "args/args.hpp"
#include "algorithms/sort.hpp"
#include "algorithms/merge_sort.hpp"
#include "arrays/arrays.hpp"

void (*FUNCTIONS[])(int *&, size_t) = {
        merge_sort,
};

std::string FUNCTION_NAMES[] = {
        "merge_sort",
};

constexpr size_t NUM_FUNCTIONS = sizeof(FUNCTIONS) / sizeof(FUNCTIONS[0]);

void run_stage(const struct BenchSettings &settings, size_t arr_size) {
    int *arr = settings.max_value
               ? random_array(arr_size, settings.max_value)
               : random_array(arr_size);
}
