#include <iostream>

#include "args/args.hpp"
#include "benchmark/benchmark.hpp"

int main(int argc, char* argv[])
{
    struct BenchSettings settings = parse_args(argc, argv);
    if (!settings.valid)
    {
        std::cerr << settings.error_message << '\n';
        return 1;
    }
    else if (settings.help)
    {
        std::cout
            << "usage: ./sorter [ --max-size N ] [ --size-step N | "
               "--num-stages N ] [ --num-runs-per-stage N ] [ --max-value N ] "
               " [ -a ALGORITHM ] [ --algorithm ALGORITHM ] [ -h ] [ --help ]"
            << std::endl;
        return 0;
    }

    benchmark(settings);
    if (settings.output != &std::cout)
        delete settings.output;

    return 0;
}