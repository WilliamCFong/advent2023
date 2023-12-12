cmake_minimum_required(VERSION 3.10)

project(days)

add_library(days
    days/day_2.c
    days/day_3.c
)

target_include_directories(days PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/days
)

add_library(
    libs
    libs/array.c
    libs/slice.c
)

target_include_directories(libs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

add_executable(day2
    days/day_2.c
)

add_executable(day3
    days/day_3.c
)

target_link_libraries(
    day2
    days
    libs
)

target_link_libraries(
    day3
    days
    libs
)
