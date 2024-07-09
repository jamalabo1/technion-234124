cmake_minimum_required(VERSION 3.16)
project(hw2-wet)

set(CMAKE_CXX_STANDARD 17)

add_library(wet_lib

        Matrix.cpp
        Matrix.h

        Utilities.cpp
        Utilities.h
        MataMvidia.h
        MataMvidia.cpp
)

target_include_directories(wet_lib PUBLIC .)

add_executable(mtests
#        tests.cpp
        more_tests.cpp
)

target_link_libraries(mtests wet-lib)