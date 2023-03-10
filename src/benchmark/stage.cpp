#include "stage.hpp"
#include <algorithm>
#include <chrono>
#include <string>
#include <iostream>
#include <cassert>
#include "args/args.hpp"
#include "algorithms/sort.hpp"
#include "algorithms/merge_sort.hpp"
#include "algorithms/bubble_sort.hpp"
#include "arrays/arrays.hpp"

void (*FUNCTIONS[])(int *&, size_t) = {
        merge_sort,
        bubble_sort,
};

std::string FUNCTION_NAMES[] = {
        "merge_sort",
        "bubble_sort",
};

constexpr size_t NUM_FUNCTIONS = sizeof(FUNCTIONS) / sizeof(FUNCTIONS[0]);

void run_stage(const struct BenchSettings &settings, size_t length) {
    /*
     * Output format:
     * array-size,num-nano-1,num-nano-2,...,num-nano-n
     */
    if (settings.output != nullptr)
        *settings.output << length;
    int *arr = settings.max_value
               ? random_array(length, settings.max_value)
               : random_array(length);
    int *arr_cpy = new int[length];
    for (size_t i = 0; i < NUM_FUNCTIONS; ++i) {
        std::cout << "Running " << FUNCTION_NAMES[i] << std::endl;
        size_t total_nano_secs = 0;
        for (size_t run = 0; run < settings.num_runs_per_stage; ++run) {
            std::copy(arr, arr + length, arr_cpy);
            // read time (t1)
            auto t1 = std::chrono::steady_clock::now();
            FUNCTIONS[i](arr_cpy, length);
            // read time (t2)
            auto t2 = std::chrono::steady_clock::now();
            // save (t2 - t1)
            auto delta_t = t2 - t1;
            total_nano_secs += delta_t.count();
            assert(is_sorted(arr_cpy, length));
        }
        // TODO: convert to ms ?
        size_t mean_time = total_nano_secs / settings.num_runs_per_stage;
        if (settings.output != nullptr)
            *settings.output << ',' << mean_time;
    }
    if (settings.output != nullptr)
        *settings.output << '\n';
    delete[] arr_cpy;
    delete[] arr;
}

void init_benchmark_output(const BenchSettings &settings) {
    if (settings.output != nullptr) {
        *settings.output << FUNCTION_NAMES[0];
        for (size_t i = 1; i < NUM_FUNCTIONS; ++i) {
            *settings.output << ',' << FUNCTION_NAMES[i];
        }
        *settings.output << '\n';
    }
}
