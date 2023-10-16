cmake_minimum_required(VERSION 3.10)

project(OOPIntro VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(classes)

add_executable(main.exe main.cpp)

target_link_libraries(main.exe PUBLIC classes)

target_include_directories(main.exe PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/classes"
                           )
