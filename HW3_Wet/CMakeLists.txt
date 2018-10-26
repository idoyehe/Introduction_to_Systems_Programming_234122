cmake_minimum_required(VERSION 3.6)
project(HW3_Wet)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")

link_directories("./libmtm/win64/libmtm.a")

set(SOURCE_FILES client.c company.c escape_room.c order.c faculty.c EscapeTechnion.c tests/EscapeTechnion_test.c)
add_executable(HW3_Wet ${SOURCE_FILES})
target_link_libraries(HW3_Wet -L. -lmtm libmtm.a)