cmake_minimum_required(VERSION 3.0)
set( CMAKE_VERBOSE_MAKEFILE ON )

project("programming-mmo")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

INCLUDE(FindPkgConfig) # Gives us PKG_SEARCH_MODULE function
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0) # There isn't a sdl2_image-config.cmake for me so we need to use this i guess

include_directories(${SDL2IMAGE_INCLUDE_DIRS})


set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

file(GLOB PROJ_INCLUDE
    "src/*.h"
)
set(SRC_DIR src)

set(PROJ_SRC
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/atom.cpp
    ${SRC_DIR}/fonts.cpp
)

add_executable(game src/main.cpp src/atom.cpp src/fonts.cpp)
target_link_libraries(game ${SDL2_LIBRARIES})
target_link_libraries(game ${OPENGL_LIBRARIES})
target_link_libraries(game ${SDL2IMAGE_LIBRARIES})
target_link_libraries(game SDL2_gfx)
target_link_libraries(game SDL2_ttf)