set (RUNTIME_SOURCES
    main.cpp
)

set (RUNTIME_HEADERS
)

add_executable(Runtime ${RUNTIME_SOURCES} 
                       ${RUNTIME_HEADERS})

target_link_libraries(Runtime
    PRIVATE
        Engine
        d3d11
        dxgi
)

target_compile_definitions(Runtime PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)