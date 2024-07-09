cmake_minimum_required(VERSION 3.16)
project(hw2)


add_subdirectory(dry)
add_subdirectory(wet)

set(ENABLE_UNIT_TESTS ON)
add_subdirectory(tests/unit-tests)