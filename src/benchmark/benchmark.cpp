#include "benchmark.hpp"

#include <iostream>

#include "stage.hpp"

#define PBSTR "############################################################"
#define PBWIDTH 60

static void print_progress(double percentage);

void benchmark(const struct BenchSettings& settings)
{
    size_t num_stages, size_increment;
    if (settings.num_stages)
    {
        num_stages = settings.num_stages;
        size_increment =
            (settings.arr_size_limit - MIN_ARR_SIZE) / (num_stages - 1);
    }
    else
    {
        size_increment = settings.arr_size_step;
        num_stages = (settings.arr_size_limit - MIN_ARR_SIZE) / size_increment;
    }
    init_benchmark_output(settings);
    size_t arr_size = MIN_ARR_SIZE;
    // arithmetic series sum formula
    size_t total_processed_size =
        num_stages * ((arr_size + settings.arr_size_limit) / 2);
    size_t curr_processed_size = 0;
    // progress bar
    int percentage = 0;
    int last_percentage = -1;

    for (size_t stage_index = 0; stage_index < num_stages; ++stage_index)
    {
        // run the stage
        run_stage(settings, arr_size);
        // progress bar
        if (settings.output != &std::cout)
        {
            if (percentage - last_percentage >= 1)
            {
                print_progress((double)percentage / 100);
                last_percentage = percentage;
            }
            curr_processed_size += arr_size;
            percentage = (int)(((size_t)100 * curr_processed_size)
                               / total_processed_size);
        }
        // prepare the next stage
        arr_size += size_increment;
    }
    if (settings.output != &std::cout)
    {
        print_progress(1.0);
        std::cout << std::endl
                  << "Done running " << num_stages << " stages" << std::endl;
    }
}

static void print_progress(double percentage)
{
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}