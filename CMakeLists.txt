# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.22)
project(hw3-src)

set(CMAKE_CXX_STANDARD 17)


add_library(
        hw3_lib

        Person.cpp
        Task.cpp
        TaskManager.cpp
)

target_include_directories(hw3_lib PUBLIC .)


add_executable(hw3_exc
        main.cpp
)

target_link_libraries(hw3_exc PUBLIC hw3_lib)