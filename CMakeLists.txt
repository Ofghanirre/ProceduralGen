cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0072 NEW)
project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)


include_directories(libs/glm/)

set(ALL_LIBRARIES libs/glm)

add_subdirectory(libs/glm)
add_subdirectory(sources)


# file(GLOB TP_DIRECTORIES "TP*")
# foreach(TP ${TP_DIRECTORIES})
#    add_subdirectory(${TP})
# endforeach()

