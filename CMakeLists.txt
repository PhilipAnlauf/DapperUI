cmake_minimum_required(VERSION 3.10)
project(DapperUI)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(
        DapperUI
        src/main.cpp
        src/Systems/ElementManager.h
        src/Systems/TextureManager.h
        src/UI/UIElement.h
        src/Systems/SceneManager.h
        src/Scenes/Scene.h
        src/Scenes/MenuScene.h
        src/UI/UIElement.h
        src/Core/DapperCore.h
        src/Scenes/Scene.h
        src/UI/Button.h
        src/UI/UIElement.cpp
        src/UI/UIElement.cpp
        src/UI/Registrar.h
        src/UI/Checkbox.h
        src/UI/TextBox.h
)

target_link_libraries(DapperUI ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

if (UNIX)
    target_link_libraries(DapperUI ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} pthread)
endif()
