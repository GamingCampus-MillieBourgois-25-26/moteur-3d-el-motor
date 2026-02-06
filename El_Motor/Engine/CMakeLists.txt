file(GLOB_RECURSE ENGINE_SOURCES
    *.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    Headers/*.hpp
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
 "Core/Source/Input_Manager/InputState.hpp")

target_sources(Engine PRIVATE Engine.cpp)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

target_link_libraries(Engine PRIVATE
    d3d11
    dxgi
    d3dcompiler
)