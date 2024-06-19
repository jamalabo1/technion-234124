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

        BlockChain.h
        Transaction.h
        Utilities.h
)

add_executable(hw1-main
        main.cpp

        Utilities.cpp

        ${headers}
        BlockChain.cpp
        Transaction.cpp
)

file(COPY tests DESTINATION .)
