cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCES
    "../libs/GameEngine/AudioManager/AudioManager.cpp"
    "../libs/GameEngine/Components/Component.cpp"
    "../libs/GameEngine/Components/Button/Button.cpp"
    "../libs/GameEngine/Entities/Entity.cpp"
    "../libs/GameEngine/Entities/Character/CharacterEntity.cpp"
    "../libs/GameEngine/Entities/Character/Player/PlayerEntity.cpp"
    "../libs/GameEngine/Entities/Character/MissileEntity/MissileEntity.cpp"
    "../libs/GameEngine/Entities/Character/Mobs/MobsEntity.cpp"
    "../libs/GameEngine/ResourcesManager/ResourceManager.cpp"
    "../libs/GameEngine/WindowManager/WindowManager.cpp"
    "../libs/GameEngine/GameEngine.cpp"
    "../libs/GameEngine/Server/ServerData.cpp"
    "../libs/GameEngine/Server/commands.cpp"
)

add_library(GameEngineLib STATIC ${LIB_SOURCES})
target_link_libraries(GameEngineLib PRIVATE sfml-audio)

set(SOURCES
    "src/main.cpp"
    "src/game.cpp"
    "src/r_type_client.cpp"
    "src/GameConfig.cpp"
    "src/Commands/Commands.cpp"
    "src/Commands/commandEvent.cpp"
    "src/Screen/ScreenGame/ScreenGame.cpp"
    "src/Screen/ScreenMenu/ScreenMenu.cpp"
    "src/Screen/ScreenOptions/ScreenOptions.cpp"
)

add_executable(r-type_client ${SOURCES})
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network pthread GL GameEngineLib)
