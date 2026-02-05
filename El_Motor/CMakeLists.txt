cmake_minimum_required(VERSION 3.16)

project(ElMotor CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Editor)
add_subdirectory("El_Motor")
add_subdirectory(Engine)