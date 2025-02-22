cmake_minimum_required(VERSION 3.29)
project(Space_Invaders)

set(CMAKE_CXX_STANDARD 17)

add_executable(Space_Invaders src/main.cpp
        include/Game.h
        src/Game.cpp
        include/ResourceHolder.h
        src/SceneNode.cpp
        include/SceneNode.h
        include/Aircraft.h
        src/Aircraft.cpp
        include/Entity.h
        src/Entity.cpp
        include/world.h
        include/SpriteNode.h
        src/world.cpp
        src/SpriteNode.cpp
        include/Command.h
        src/Command.cpp
        include/Player.h
        src/Player.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

include_directories(C:/SFML/include)
find_package(SFML REQUIRED system window graphics)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Space_Invaders ${SFML_LIBRARIES})
endif ()
