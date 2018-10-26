cmake_minimum_required(VERSION 3.6)
project(part2)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")


set(SOURCE_FILES mtm_buggy.c)
add_executable(part2 ${SOURCE_FILES})