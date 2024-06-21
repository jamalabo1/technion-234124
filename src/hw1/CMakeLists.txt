cmake_minimum_required(VERSION 3.19)
project(project-hw1)

set(CMAKE_CXX_STANDARD 17)


set(headers

        files/BlockChain.h
        files/Transaction.h
        files/Utilities.h
)

add_executable(mtm_blockchain
        ${headers}

        files/main.cpp
        files/Utilities.cpp
        files/BlockChain.cpp
        files/Transaction.cpp
)

install_project_binaries(mtm_blockchain )