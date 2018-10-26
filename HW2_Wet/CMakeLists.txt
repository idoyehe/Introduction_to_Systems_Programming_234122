cmake_minimum_required(VERSION 3.6)
project(HW2_Wet)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror ")

set(SOURCE_FILES challenge.c visitor_room.c challenge_system.c
        challenge_system_test_1.c)
add_executable(HW2_Wet ${SOURCE_FILES})