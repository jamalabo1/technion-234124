# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.19)
project(project-hw1)

set(CMAKE_CXX_STANDARD 17)


set(headers

        files/BlockChain.h
        files/Transaction.h
        files/Utilities.h
)

add_executable(hw1-main
        ${headers}

        files/main.cpp
        files/Utilities.cpp
        files/BlockChain.cpp
        files/Transaction.cpp
)

install_project_binaries(hw1-main)