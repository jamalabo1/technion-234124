cmake_minimum_required(VERSION 3.16)
project(hw2-wet)

set(CMAKE_CXX_STANDARD 17)

add_library(wet-lib

        Matrix.cpp
        Matrix.h

        Utilities.cpp
        Utilities.h
        MataMvidia.h
        MataMvidia.cpp
)


add_executable(tests
#        tests.cpp
        more_tests.cpp
)

target_link_libraries(tests wet-lib)