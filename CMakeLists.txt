# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (Procedural_Generation)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(
        -std=c++14
    )
endif()

message("Starting compilation for Project ${CMAKE_PROJECT_NAME}")

# Create a sources variable with a link to all cpp files to compile
file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/sources/*.h
        ${PROJECT_SOURCE_DIR}/sources/*.hpp
)

# Add an executable with the above sources
add_executable(procGen ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(procGen
        PRIVATE
        ${PROJECT_SOURCE_DIR}/sources
)