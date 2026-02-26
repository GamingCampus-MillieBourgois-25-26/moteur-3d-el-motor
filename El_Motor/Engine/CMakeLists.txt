# Regen with this: cmake . -G "Visual Studio 17" -B out

file(GLOB_RECURSE ENGINE_SOURCES
    Core/src/**/*.cpp 
    Components/UserComponents/**/*.cpp
)



file(GLOB_RECURSE ENGINE_HEADERS
    Core/Headers/**/*.hpp
    Components/UserComponents/**/*.hpp
    Externals/**/*.h
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers 
                                         ${CMAKE_CURRENT_SOURCE_DIR}/Externals
                                         ${CMAKE_CURRENT_SOURCE_DIR}/Core/Headers
                                         ${CMAKE_CURRENT_SOURCE_DIR}/Components/UserComponents/Headers

)


target_link_libraries(Engine PRIVATE
    glfw
    d3d11
    dxgi
    d3dcompiler
)