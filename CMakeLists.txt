cmake_minimum_required(VERSION 3.21)


project(mario)
set(CMAKE_CXX_STANDARD 23)
find_package(OpenGL REQUIRED)
#find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)


# DIR="external"
#git clone https://github.com/Microsoft/vcpkg.git "$DIR/vcpkg"
#    cd "$DIR/vcpkg"
#    ./bootstrap-vcpkg.sh
#    ./vcpkg integrate install
#    ./vcpkg install jsoncpp
#doas pacman -S jsoncpp

file(GLOB_RECURSE SOURCES ./src/*.cpp)



add_executable(mario
        libs/glad/src/glad.c
        ${SOURCES}
        libs/std_image/std_image.h
        libs/std_image/std_image.cpp src/game/objects/Bitcoin.cpp src/game/objects/Bitcoin.h src/game/objects/Ground.cpp src/game/objects/Ground.h src/game/objects/BackgroundObject.cpp src/game/objects/BackgroundObject.h src/game/objects/Fireball.cpp src/game/objects/Fireball.h)


# include so file

target_link_libraries(mario ${CMAKE_CURRENT_SOURCE_DIR}/libs/irrKlang/lib/libIrrKlang.so)

target_link_libraries(mario ${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/lib/libglfw.so)


target_link_libraries(mario glfw dl)
target_link_libraries(mario OpenGL::GL)
target_link_libraries(mario ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${JSON_INC_PATH})
target_link_libraries(${PROJECT_NAME}
        #...
        jsoncpp
        )
target_link_directories(${PROJECT_NAME} PUBLIC ${JSON_LIB_PATH})
target_include_directories(mario PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(mario PRIVATE ./libs)