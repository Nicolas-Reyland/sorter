#include "benchmark.hpp"

#include <iostream>

#include "stage.hpp"

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
    for (size_t stage_index = 0; stage_index < num_stages; ++stage_index)
    {
        std::cout << "Starting stage " << stage_index + 1 << "/" << num_stages
                  << std::endl;
        // run the stage
        run_stage(settings, arr_size);
        // prepare the next stage
        arr_size += size_increment;
    }
    std::cout << "Done running all the " << num_stages << " stages"
              << std::endl;
}