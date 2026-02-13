# Regen with this: cmake . -G "Visual Studio 17" -B out

file(GLOB_RECURSE ENGINE_SOURCES
    Core/src/**/*.cpp 
    cpnt/**/*.cpp

)

file(GLOB_RECURSE ENGINE_HEADERS
    Core/Headers/**/*.hpp
    cpnt/**/*.hpp
    Externals/**/*.h
)

add_library(Engine
    ${ENGINE_HEADERS}
    ${ENGINE_SOURCES}
)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers 
                                         ${CMAKE_CURRENT_SOURCE_DIR}/Externals
                                         ${CMAKE_CURRENT_SOURCE_DIR}/Core/Headers)


target_link_libraries(Engine PRIVATE
    glfw
    d3d11
    dxgi
    d3dcompiler    
)