cmake_minimum_required(VERSION 3.16)

project(ElMotor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw)

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Runtime)
add_subdirectory(MathLib)
add_subdirectory(UnitTest)