cmake_minimum_required(VERSION 3.24)
project(sorter)

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_executable(sorter)

set_target_properties(sorter PROPERTIES
        CXX_STANDARD 20)

add_subdirectory(src)
