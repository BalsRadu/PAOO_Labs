# The contents of this file were taken from the OOP_Intro directory and sligly modified
# to work with the new directory structure
cmake_minimum_required(VERSION 3.10)

project(MyStringArray VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dynamic_string_array)

add_executable(MyStringArray main.cpp)

target_link_libraries(MyStringArray PUBLIC dynamic_string_array)

target_include_directories(MyStringArray PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/dynamic_string_array"
                           )