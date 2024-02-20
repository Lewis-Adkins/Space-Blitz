cmake_minimum_required(VERSION 3.0.0)
project(Space_Blitz VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_library(SDL2_IMAGE_LIBRARY SDL2_image)

if(NOT SDL2_IMAGE_LIBRARY)
    message(FATAL_ERROR "SDL2_image library not found")
endif()

add_executable(Space_Blitz
    src/main.cpp

    src/Game.cpp
    src/Game.hpp

    src/TextureManager.cpp
    src/TextureManager.hpp

    src/GameObject.cpp
    src/GameObject.hpp
    
    src/Background.cpp
    src/Background.hpp

    src/Vector2D.hpp
    src/Vector2D.cpp

    src/Collision.hpp
    src/Collision.cpp

    src/ECS/Components.hpp
    src/ECS/ECS.hpp
    src/ECS/TransformComponent.hpp
    src/ECS/SpriteComponent.hpp
    src/ECS/KeyboardController.hpp
    src/ECS/ColliderComponent.hpp
)

target_link_libraries(Space_Blitz PRIVATE SDL2 SDL2main ${SDL2_IMAGE_LIBRARY})
