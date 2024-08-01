# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.22)
project(technion-234124)

set(CMAKE_CXX_STANDARD 17)


add_library(matam4-utilites
        Utilities.cpp
        Utilities.h
)

target_include_directories(matam4-utilites PUBLIC .)

add_library(matam4

        MatamStory.cpp
        Players/Warrior.h
        Players/Archer.h
        "Players/Magician.h"
        Behaviours/Behaviour.h
        Behaviours/RiskTaking.h
        Events/SpecialEvent.h
        Events/EncounterEvent.h
)

target_link_libraries(matam4 PUBLIC matam4-utilites)
target_include_directories(matam4 PUBLIC .)

add_executable(matam4-exc
         main.cpp
)