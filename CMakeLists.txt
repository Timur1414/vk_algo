cmake_minimum_required(VERSION 3.29)
project(vk_algo)

set(CMAKE_CXX_STANDARD 23)

add_executable(vk_algo
        "3 module/1/main.cpp"
        "3 module/1/include/arc_graph.h"
        "3 module/1/include/list_graph.h"
        "3 module/1/include/matrix_graph.h"
        "3 module/1/include/set_graph.h")
