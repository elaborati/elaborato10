cmake_minimum_required(VERSION 3.21)
project(elaborato10 C)

set(CMAKE_C_STANDARD 90)

add_executable(elaborato10 main.c cl_bigint.c dl_bigint.c cl_bigint.h dl_bigint.h)