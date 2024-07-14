cmake_minimum_required(VERSION 3.16)
project(technion-234124)

set(CMAKE_CXX_STANDARD 17)


if (ENABLE_UNIT_TESTS)
    include(cmake/utils.cmake)
    include(cmake/FindGTest.cmake)

    message(STATUS "Unit tests enabled")
    set(TESTING_TARGET_LIBRARY wet_lib)

    set(GLOBAL_TESTING_TARGET tests)
    message(STATUS "GLOBAL TARGET: ${GLOBAL_TESTING_TARGET}, TESTING_TARGET_LIBRARY: ${TESTING_TARGET_LIBRARY}")

    create_global_testing_target(${GLOBAL_TESTING_TARGET} main.cpp) # create a global target for sub-tests to link their test library to

    # start TESTING_TARGET_LIBRARY
    add_library(${TESTING_TARGET_LIBRARY}_tests
            matrix/matrix_constructor_tests.cpp
            matrix/matrix_index_operator_tests.cpp
            matrix/matrix_operators_tests.cpp
            matrix/MatrixTestBase.cpp
            matrix/MatrixTestBase.h
            matrix/matrix_methods_tests.cpp
            MataMvidia/matamvidia_constructor_tests.cpp
    )

    add_library(
            test-utils
            utils.cpp
            utils.h
    )
    target_sources(test-utils PUBLIC utils.h)
    target_include_directories(test-utils PUBLIC .)

    target_link_libraries(${TESTING_TARGET_LIBRARY}_tests PUBLIC test-utils)

    create_testing_target(${TESTING_TARGET_LIBRARY})
    #end TESTING_TARGET_LIBRARY

    create_testing_executable(${GLOBAL_TESTING_TARGET} ${GLOBAL_TESTING_TARGET}_exc)
    #    enable_global_testing_target() # enable this target by linking the global target to an executable (order is important, for the global test target to populate it's self)

    install(TARGETS ${GLOBAL_TESTING_TARGET}_exc DESTINATION bin COMPONENT ${GLOBAL_TESTING_TARGET}_exc)
endif ()