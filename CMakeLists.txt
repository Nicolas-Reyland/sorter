cmake_minimum_required(VERSION 3.24)
project(sorter)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Werror -pedantic)

add_executable(sorter)

add_subdirectory(src)
