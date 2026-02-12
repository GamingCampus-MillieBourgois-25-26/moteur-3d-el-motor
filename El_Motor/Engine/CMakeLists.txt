# Regen with this: cmake . -G "Visual Studio 17" -B out

file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(Engine
    ${ENGINE_HEADERS}
    ${ENGINE_SOURCES}
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Engine PRIVATE
    glfw
    d3d11
    dxgi
    d3dcompiler    
)