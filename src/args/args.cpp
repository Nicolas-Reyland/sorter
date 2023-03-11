#include "args.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "benchmark/stage.hpp"

#define ARG_IS(Name) (strcasecmp(argv[i], "--" Name) == 0)
#define SHORT_ARG_IS(Name) (strcasecmp(argv[i], "-" Name) == 0)

#define ASSERT_ARG_HAS_VALUE                                                   \
    if (i == max_i)                                                            \
    {                                                                          \
        settings.valid = false;                                                \
        settings.error_message =                                               \
            "The param " + std::string(argv[i]) + " needs a value";            \
        break;                                                                 \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        ++i;                                                                   \
    }

const size_t MIN_ARR_SIZE = 5;
const size_t DF_NUM_STAGES = 1000;

const std::vector<std::string> DF_ALGORITHMS = {
    "merge_sort",
    "tim_sort",
    "quick_sort",
    "intro_sort",
};

struct BenchSettings parse_args(int argc, char** argv)
{
    struct BenchSettings settings
    {};
    // TODO: validate values
    settings.help = argc < 2;

    int max_i = argc - 1;
    for (int i = 1; i < argc; ++i)
    {
        std::stringstream arg_stream(i == max_i ? argv[i] : argv[i + 1]);
        if (ARG_IS("max-size"))
        {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.arr_size_limit;
        }
        else if (ARG_IS("size-step"))
        {
            ASSERT_ARG_HAS_VALUE
            if (settings.num_stages)
            {
                settings.valid = false;
                settings.error_message =
                    "Cannot indicate both num-stages and size-step";
                break;
            }
            arg_stream >> settings.arr_size_step;
        }
        else if (ARG_IS("num-runs-per-stage"))
        {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.num_runs_per_stage;
        }
        else if (ARG_IS("num-stages"))
        {
            ASSERT_ARG_HAS_VALUE
            if (settings.arr_size_step)
            {
                settings.valid = false;
                settings.error_message =
                    "Cannot indicate both num-stages and size-step";
                break;
            }
            arg_stream >> settings.num_stages;
        }
        else if (ARG_IS("max-value"))
        {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.max_value;
        }
        else if (SHORT_ARG_IS("o") || ARG_IS("output"))
        {
            ASSERT_ARG_HAS_VALUE
            settings.output = new std::ofstream(argv[i]);
        }
        else if (SHORT_ARG_IS("a") || ARG_IS("algorithm"))
        {
            ASSERT_ARG_HAS_VALUE
            std::string name = argv[i];
            if (!DEFINED_ALGORITHMS.contains(name))
            {
                settings.error_message = "The algorithm " + name
                    + " is not known.\nThe known algorithms are:";
                for (auto [key, _] : DEFINED_ALGORITHMS)
                    settings.error_message += "\n - " + key;
                settings.valid = false;
                break;
            }
            settings.algorithms.push_back(name);
        }
        else if (SHORT_ARG_IS("h") || ARG_IS("help"))
        {
            settings.help = true;
            break;
        }
        else
        {
            settings.valid = false;
            settings.error_message =
                std::string("Unknown option: ") + std::string(argv[i]);
            break;
        }
    }

    // default values
    if (!(settings.num_stages || settings.arr_size_step))
        settings.num_stages = DF_NUM_STAGES;
    if (settings.algorithms.empty())
        settings.algorithms = DF_ALGORITHMS;
    if (settings.output == nullptr)
        settings.output = &std::cout;

    return settings;
}

BenchSettings::~BenchSettings() = default;
