set (ENGINE_SOURCES
    Core/Source/Window/Window.cpp
)

set (ENGINE_HEADERS
    Core/Headers/Window/Window.hpp
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_compile_definitions(Engine PRIVATE ENGINE_BUILD_DLL)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core/Headers)

target_link_libraries(Engine PUBLIC
    glfw
    d3d11
    dxgi
    d3dcompiler 
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ENGINE_SOURCES} ${ENGINE_HEADERS})