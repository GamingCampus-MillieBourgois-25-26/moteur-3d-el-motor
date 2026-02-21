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

FetchContent_Declare(
    MathLib
    GIT_REPOSITORY https://github.com/GamingCampus-MillieBourgois-25-26/3d-geometry-club-ceinture.git
    GIT_TAG gold
)

FetchContent_Declare(
    JoltPhysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG 5.5.0
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw 3d-geometry-club-ceinture JoltPhysics)

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Runtime)