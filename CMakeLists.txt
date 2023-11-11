cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0072 NEW)
project(ProceduralGen)

add_definitions(-std=c++14)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} lib/include)

set(ALL_LIBRARIES lib ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${SDL2_LIBRARIES})

add_subdirectory(lib)

# set(SRC_DIRECTORY "src")

add_subdirectory(src)
