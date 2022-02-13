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

file(GLOB_RECURSE SOURCES ./src/*.cpp)

add_executable(mario
        libs/glad/src/glad.c
        ${SOURCES}
        libs/std_image/std_image.h
        libs/std_image/std_image.cpp
        )
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