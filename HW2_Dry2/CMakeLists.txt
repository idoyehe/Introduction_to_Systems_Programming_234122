cmake_minimum_required(VERSION 3.6)
project(HW2_Dry2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")

set(SOURCE_FILES dryEx2.c)
add_executable(HW2_Dry2 ${SOURCE_FILES})