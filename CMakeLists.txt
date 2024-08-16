# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.22)
project(technion-234124)

set(CMAKE_CXX_STANDARD 17)




add_library(matam4-lib

        include/Factory.h
        impl/Factory.cpp

        MatamStory.cpp
        impl/Players/Player.cpp

        include/Strategy/Strategy.h
        include/Strategy/RiskTaking.h

        include/Events/EncounterEvent.h
        include/Events/SpecialEvent.h

        include/Players/Player.h
        include/Players/Archer.h
        include/Players/Magician.h
        include/Players/Warrior.h
        include/Strategy/Responsible.h

        impl/Players/Warior.cpp
        impl/Strategy/Responsible.cpp
        impl/Strategy/RiskTaking.cpp
        impl/Players/Magician.cpp
        impl/Players/Archer.cpp
        impl/Events/EncounterEvent.cpp
        impl/Events/SpecialEvent.cpp

        include/Loaders.h

        Utilities.cpp
        Utilities.h
)

target_include_directories(matam4-lib PUBLIC include)

add_executable(matam4-exc
         main.cpp
)

target_link_libraries(matam4-exc PUBLIC matam4-lib)

file(COPY tests DESTINATION .)
file(COPY simple_test_runner.py DESTINATION .)
file(COPY run_tests.py DESTINATION .)