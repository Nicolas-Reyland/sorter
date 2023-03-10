#pragma once

#include <cstddef>
#include <string>

extern const size_t MIN_ARR_SIZE;

struct BenchSettings {
    size_t arr_size_limit = 1E6;
    size_t arr_size_step = 0; // 0 : auto (see num_stages)
    size_t num_runs_per_stage = 3;
    size_t num_stages = 0; // 0 : auto (see arr_size_step)
    int max_value = 0; // no max value
    std::ostream* output = nullptr;
    bool valid = true;
    std::string error_message = "success";
    bool help = false;
    ~BenchSettings();
};

struct BenchSettings parse_args(int argc, char *argv[]);
