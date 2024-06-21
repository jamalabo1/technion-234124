cmake_minimum_required(VERSION 3.19)
project(technion-234124)

set(CMAKE_CXX_STANDARD 17)

add_custom_target(test)


add_custom_command(
        TARGET test POST_BUILD
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND pip install click --target ${PROJECT_BINARY_DIR}/engine
        COMMENT "Copying engine.py file"
)

#
#add_custom_command(
#        TARGET test POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_CURRENT_LIST_DIR}/engine.py
#        ${PROJECT_BINARY_DIR}/engine.py
#        COMMENT "Copying engine.py file"
#)
#



install(
        DIRECTORY
        engine
        DESTINATION bin
)

install(
        DIRECTORY
        ${PROJECT_BINARY_DIR}/engine
        DESTINATION bin
)

install(FILES
        settings.json
        DESTINATION bin
)
install(
        DIRECTORY
        hw1-tests
        DESTINATION bin
)
