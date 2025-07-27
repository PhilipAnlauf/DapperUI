cmake_minimum_required(VERSION 3.31)
project(CommissarOfProduction)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        DapperUI src/main.cpp
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
        src/UI/Registrar.h)
