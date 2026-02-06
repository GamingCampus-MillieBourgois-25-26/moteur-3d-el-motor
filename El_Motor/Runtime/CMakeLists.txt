add_executable(Runtime main.cpp)

target_link_libraries(Runtime PRIVATE
    Engine
    glfw
    d3d11
    dxgi
)

target_compile_definitions(Runtime PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)