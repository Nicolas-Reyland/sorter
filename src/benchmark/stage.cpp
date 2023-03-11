#include "stage.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "algorithms/bubble_sort.hpp"
#include "algorithms/intro_sort.hpp"
#include "algorithms/merge_sort.hpp"
#include "algorithms/quick_sort.hpp"
#include "algorithms/tim_sort.hpp"
#include "args/args.hpp"
#include "arrays/arrays.hpp"

static const std::map<std::string, void (*)(int*&, size_t)> FUNCTIONS = {
    { "bubble_sort", &bubble_sort }, { "merge_sort", &merge_sort },
    { "tim_sort", &tim_sort },       { "quick_sort", &quick_sort },
    { "intro_sort", &intro_sort },
};

static const std::vector<std::string> FUNCTION_NAMES = {
    "merge_sort",
    "tim_sort",
    "quick_sort",
    "intro_sort",
};

void run_stage(const struct BenchSettings& settings, size_t length)
{
    /*
     * Output format:
     * array-size,num-nano-1,num-nano-2,...,num-nano-n
     */
    if (settings.output != nullptr)
        *settings.output << length;
    int* arr = settings.max_value ? random_array(length, settings.max_value)
                                  : random_array(length);
    int* arr_cpy = new int[length];
    for (const auto& fn_name : FUNCTION_NAMES)
    {
        auto function = FUNCTIONS.find(fn_name)->second;
        size_t total_nano_secs = 0;
        for (size_t run = 0; run < settings.num_runs_per_stage; ++run)
        {
            std::copy(arr, arr + length, arr_cpy);
            // read time (t1)
            auto t1 = std::chrono::steady_clock::now();
            function(arr_cpy, length);
            // read time (t2)
            auto t2 = std::chrono::steady_clock::now();
            // save (t2 - t1)
            auto delta_t = t2 - t1;
            total_nano_secs += delta_t.count();
            assert(is_sorted(arr_cpy, length));
        }
        // µs
        size_t mean_micro_secs =
            total_nano_secs / (1000 * settings.num_runs_per_stage);
        if (settings.output != nullptr)
            *settings.output << ',' << mean_micro_secs;
    }
    if (settings.output != nullptr)
        *settings.output << '\n';
    delete[] arr_cpy;
    delete[] arr;
}

void init_benchmark_output(const BenchSettings& settings)
{
    if (settings.output != nullptr)
    {
        *settings.output << FUNCTION_NAMES[0];
        for (size_t i = 1; i < FUNCTION_NAMES.size(); ++i)
            *settings.output << ',' << FUNCTION_NAMES[i];

        *settings.output << '\n';
    }
}
