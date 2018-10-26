cmake_minimum_required(VERSION 3.6)
project(HW3_Dry)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES  list.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror ")

add_executable(HW3_Dry ${SOURCE_FILES})