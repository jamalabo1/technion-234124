cmake_minimum_required(VERSION 3.16)
project(technion-234124)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(cmake/core.cmake)
include(cmake/utils.cmake)

message (STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")


add_subdirectory(src)
