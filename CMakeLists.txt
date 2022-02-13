cmake_minimum_required(VERSION 3.21)
project(mario)

set(CMAKE_CXX_STANDARD 23)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)
set(JSON_INC_PATH /home/peu77/vcpkg/packages/jsoncpp_x64-osx/include)
# DIR="external"
#git clone https://github.com/Microsoft/vcpkg.git "$DIR/vcpkg"
#    cd "$DIR/vcpkg"
#    ./bootstrap-vcpkg.sh
#    ./vcpkg integrate install
#    ./vcpkg install jsoncpp
#doas pacman -S jsoncpp

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
        src/game/texture/Texture.h
        src/game/texture/Texture.cpp
        libs/std_image/std_image.h
        libs/std_image/std_image.cpp
        src/game/objects/Enemy.cpp
        src/game/objects/Enemy.h
        src/game/physic/World.cpp
        src/game/physic/World.h
        src/window/Screen.h
        src/game/screens/ScreenMain.cpp
        src/game/screens/ScreenMain.h src/game/Animation.cpp src/game/Animation.h src/game/screens/ScreenEditor.cpp src/game/screens/ScreenEditor.h)
target_link_libraries(mario glfw dl)
target_link_libraries(mario OpenGL::GL)
target_link_libraries(mario ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${JSON_INC_PATH})
set(JSON_LIB_PATH /home/peu77/vcpkg/packages/jsoncpp_x64-osx/include)
target_link_libraries(${PROJECT_NAME}
        #...
        jsoncpp
        )
target_link_directories(${PROJECT_NAME} PUBLIC ${JSON_LIB_PATH})
target_include_directories(mario PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(mario PRIVATE ./libs)