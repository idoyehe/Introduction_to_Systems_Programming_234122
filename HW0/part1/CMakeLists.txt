cmake_minimum_required(VERSION 3.6)
project(part1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")

set(SOURCE_FILES part1.c)
add_executable(part1 ${SOURCE_FILES} part1.c)