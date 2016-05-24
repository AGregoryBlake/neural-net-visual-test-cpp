cmake_minimum_required(VERSION 2.8)
project(neural-net-visual-test-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter")

set(BUILD_SHARED_LIBRARIES OFF) 

### BOX2D 
include(ExternalProject) 
set(sdl_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/sdl") 
set(sdl_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/sdl") 
set(sdl_DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/sdl/download") 
set(sdl_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sdl_INSTALL_DIR}) 

ExternalProject_Add(SDL 
    PREFIX ${sdl_PREFIX} 
    URL http://www.libsdl.org/tmp/SDL-2.0.zip 
    INSTALL_DIR ${sdl_INSTALL_DIR} 
    CMAKE_ARGS ${sdl_CMAKE_ARGS} 
) 

include_directories("${CMAKE_CURRENT_BINARY_DIR}/sdl/include") 

add_executable(neural-net-visual-test-cpp main.cpp) 

target_link_libraries(neural-net-visual-test-cpp ${sdl_PREFIX}/lib/libSDL2.a pthread dl)

add_dependencies(neural-net-visual-test-cpp SDL)