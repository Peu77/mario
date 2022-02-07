cmake_minimum_required(VERSION 3.21)
project(mario)

set(CMAKE_CXX_STANDARD 23)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(box2d REQUIRED)
add_executable(mario
        src/main.cpp
        libs/glad/src/glad.c
        src/window/Window.cpp
        src/window/Window.h
        src/game/Game.cpp
        src/game/Game.h
        src/game/shader/Shader.h
        src/game/shader/Shader.cpp
        src/game/shader/Program.h
        src/game/shader/Program.cpp
        src/game/renderer/Renderer.cpp
        src/game/renderer/Renderer.h
        src/game/camera/Camera.cpp
        src/game/camera/Camera.h
        src/game/GlmInclude.h
        src/game/objects/GameObject.h
        src/game/objects/Brick.cpp
        src/game/objects/Brick.h
        src/game/objects/Mario.cpp
        src/game/objects/Mario.h
        src/game/Box2dInclude.h
        src/game/collisionListener/CollisionListener.cpp
        src/game/collisionListener/CollisionListener.h
        src/game/texture/Texture.h
        src/game/texture/Texture.cpp
        libs/std_image/std_image.h
        libs/std_image/std_image.cpp)
target_link_libraries(mario glfw dl)
target_link_libraries(mario box2d dl)
target_link_libraries(mario OpenGL::GL)

target_include_directories(mario PRIVATE ./libs)