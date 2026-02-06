file(GLOB_RECURSE RUNTIME_SOURCES
	*.cpp
)

file(GLOB_RECURSE RUNTIME_HEADERS
	Headers/*.hpp
)

add_executable(Runtime ${RUNTIME_SOURCES} 
                       ${RUNTIME_HEADERS})

target_link_libraries(Runtime
    PRIVATE
        Engine
        glfw
        d3d11
        dxgi
)

