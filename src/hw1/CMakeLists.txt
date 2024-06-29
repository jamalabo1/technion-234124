cmake_minimum_required(VERSION 3.16)
project(project-hw1)

set(CMAKE_CXX_STANDARD 17)


set(headers

        files/BlockChain.h
        files/Transaction.h
        files/Utilities.h
)

add_library(mtm_blockchain_lib
        ${headers}
        
        files/Utilities.cpp
        files/BlockChain.cpp
        files/Transaction.cpp
)

target_include_directories(
        mtm_blockchain_lib

        PUBLIC

        files
)

add_executable(
        mtm_blockchain

        files/main.cpp
)

target_link_libraries(mtm_blockchain mtm_blockchain_lib)


install_project_binaries(mtm_blockchain)