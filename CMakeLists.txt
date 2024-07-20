# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.22)
project(technion-234124-hw3)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(src)