cmake_minimum_required(VERSION 3.6)
project(HW4_WET)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")

set(SOURCE_FILES Company.cpp ./tests/Company_test.cpp EscapeRoom.c EscapeRoomWrapper.cpp Enigma.cpp ScaryRoom.cpp KidsRoom.cpp)
add_executable(HW4_WET ${SOURCE_FILES})