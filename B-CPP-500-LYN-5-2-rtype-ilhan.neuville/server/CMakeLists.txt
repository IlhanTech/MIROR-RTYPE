cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/r_type_server.cpp
    src/commands/commands.cpp
    src/commands/command_list.cpp
    src/Entity/Entity.cpp
    src/Entity/Player/Player.cpp
    src/unique_id_generation.cpp
    src/Game/Game.cpp
)

add_executable(r-type_server ${SOURCES})
target_link_libraries(r-type_server PRIVATE sfml-network)
