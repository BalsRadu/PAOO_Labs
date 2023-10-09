cmake_minimum_required(VERSION 3.10) # Minimum version of CMake required

project(Tutorial VERSION 1.0) # Project version

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED True) # ...is required...


configure_file(TutorialConfig.h.in TutorialConfig.h) 

add_executable(Tutorial tutorial.cxx)


target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
