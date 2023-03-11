#pragma once

#include <cstddef>
#include <map>
#include <string>

extern const std::map<std::string, void (*)(int*&, size_t)> DEFINED_ALGORITHMS;

void run_stage(const struct BenchSettings& settings, size_t length);

void init_benchmark_output(const struct BenchSettings& settings);