target_include_directories(sorter PRIVATE .)
target_sources(sorter PRIVATE main.cpp)

add_subdirectory(algorithms)
add_subdirectory(arrays)
add_subdirectory(printer)
add_subdirectory(benchmark)
add_subdirectory(args)
