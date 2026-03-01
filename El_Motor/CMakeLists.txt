cmake_minimum_required(VERSION 3.16)

project(ElMotor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

set(JOLT_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(JOLT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JOLT_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

FetchContent_Declare(
    JoltPhysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG v5.5.0
)

FetchContent_MakeAvailable(glfw JoltPhysics)

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Runtime)
add_subdirectory(Game)
