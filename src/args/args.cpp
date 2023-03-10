#include <cstring>
#include <sstream>
#include <iostream>
#include "args.hpp"

#define ARG_IS(Name) (strcasecmp(argv[i], "--" Name) == 0)
#define SHORT_ARG_IS(Name) (strcasecmp(argv[i], "-" Name) == 0)

#define ASSERT_ARG_HAS_VALUE \
        if (i == max_i) {      \
        settings.valid = false;                           \
        settings.error_message = "The param " + std::string(argv[i]) + " needs a value";       \
        break; \
    } else { ++i; }

const size_t MIN_ARR_SIZE = 5;
const size_t DF_NUM_STAGES = 1000;

struct BenchSettings parse_args(int argc, char **argv) {
    struct BenchSettings settings{};
    // TODO: validate values

    int max_i = argc - 1;
    for (int i = 1; i < argc; ++i) {
        std::stringstream arg_stream(i == max_i ? argv[i] : argv[i + 1]);
        if (ARG_IS("max-size")) {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.arr_size_limit;
        } else if (ARG_IS("size-step")) {
            ASSERT_ARG_HAS_VALUE
            if (settings.num_stages) {
                settings.valid = false;
                settings.error_message = "Cannot indicate both num-stages and size-step";
                break;
            }
            arg_stream >> settings.arr_size_step;
        } else if (ARG_IS("num-runs-per-stage")) {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.num_runs_per_stage;
        } else if (ARG_IS("num-stages")) {
            ASSERT_ARG_HAS_VALUE
            if (settings.arr_size_step) {
                settings.valid = false;
                settings.error_message = "Cannot indicate both num-stages and size-step";
                break;
            }
            arg_stream >> settings.num_stages;
        } else if (ARG_IS("max-value")) {
            ASSERT_ARG_HAS_VALUE
            arg_stream >> settings.max_value;
        } else if (SHORT_ARG_IS("h") || ARG_IS("help")) {
            settings.help = true;
            break;
        } else {
            settings.valid = false;
            settings.error_message = std::string("Unknown option: ") + std::string(argv[i]);
            break;
        }
    }

    if (!(settings.num_stages || settings.arr_size_step))
        settings.num_stages = DF_NUM_STAGES;

    return settings;
}
