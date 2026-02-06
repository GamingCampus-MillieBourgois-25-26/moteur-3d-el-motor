file(GLOB_RECURSE EDITOR_SOURCES
	*.cpp
)

add_executable(Editor ${EDITOR_SOURCES})

target_link_libraries(Editor PRIVATE
    Engine
    glfw
    d3d11
    dxgi
)

target_compile_definitions(Editor PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)