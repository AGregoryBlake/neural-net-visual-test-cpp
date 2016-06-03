cmake_minimum_required(VERSION 2.8)
project(neural-net-visual-test-cpp)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin/${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m64 -Dmain=SDL_main")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64" )

include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

set(SOURCE_FILES main.cpp app.h neural.h)
add_executable(neural-net-visual-test-cpp ${SOURCE_FILES})

target_link_libraries(neural-net-visual-test-cpp "mingw32")
target_link_libraries(neural-net-visual-test-cpp "SDL2main")
target_link_libraries(neural-net-visual-test-cpp "SDL2")