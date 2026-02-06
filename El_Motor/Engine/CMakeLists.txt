file(GLOB_RECURSE ENGINE_SOURCES
    Source/*.cpp
    Core/Source/Window/*.cpp 
    Component/UserComponents/Camera/Source/Camera.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    Headers/*.hpp
    Headers/*.h
    Core/Source/Input_Manager/InputState.hpp
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
 "Core/Source/Window/Window.cpp")

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

target_link_libraries(Engine PRIVATE
    d3d11
    dxgi
    d3dcompiler
    
)