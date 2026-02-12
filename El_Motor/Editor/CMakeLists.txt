file(GLOB_RECURSE EDITOR_SOURCES
	src/**/*.cpp
)

file(GLOB_RECURSE EDITOR_HEADERS
	 Headers/**/*.hpp
)

add_executable(Editor ${EDITOR_SOURCES} 
                      ${EDITOR_HEADERS}
                      src/Main/Editor.cpp
 )

target_link_libraries(Editor PRIVATE
    Engine
    glfw
    d3d11
    dxgi
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

target_compile_definitions(Editor PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)