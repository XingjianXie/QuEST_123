cmake_minimum_required(VERSION 3.10)

project(QuEST_123)

set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=native")

add_executable(QuEST_123 main.c)
