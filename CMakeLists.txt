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

        Factory.h
        Factory.cpp

        MatamStory.cpp
        Players/Player.cpp

        Players/Strategy.h
        Players/RiskTaking.h

        Events/EncounterEvent.h
        Events/SpecialEvent.h

        Players/Player.h
        Players/Archer.h
        Players/Magician.h
        Players/Warrior.h
        Players/Responsible.h

        Players/Warior.cpp
        Players/Responsible.cpp
        Players/RiskTaking.cpp
        Players/Magician.cpp
        Players/Archer.cpp
        Events/EncounterEvent.cpp
        Events/SpecialEvent.cpp

        Loaders.h

        Utilities.cpp
        Utilities.h
)

target_include_directories(matam4-lib PUBLIC include)

add_executable(matam4-exc
        main.cpp
)

target_link_libraries(matam4-exc PUBLIC matam4-lib)

file(COPY tests DESTINATION .)
file(COPY run_tests.py DESTINATION .)


add_custom_command(
        TARGET matam4-exc POST_BUILD
        COMMAND python3 run_tests.py ./matam4-exc ./tests/custom_tests.json
        WORKING_DIRECTORY $<TARGET_FILE_DIR:matam4-exc>
)