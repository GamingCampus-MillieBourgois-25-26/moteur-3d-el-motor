
file(GLOB IMGUI_CORE_SOURCES
    External/ImGui/src/CoreSource/**/*.cpp
)

file(GLOB IMGUI_BACKEND_SOURCES
    External/ImGui/src/Backend/imgui_impl_glfw.cpp
    External/ImGui/src/Backend/imgui_impl_dx11.cpp
)

add_library(imgui_lib STATIC ${IMGUI_CORE_SOURCES} ${IMGUI_BACKEND_SOURCES})


file(GLOB_RECURSE EDITOR_SOURCES
	src/**/*.cpp
    External/ImGui/src/**/*.cpp
)

file(GLOB_RECURSE EDITOR_HEADERS
	 Headers/**/*.hpp
     External/ImGui/Headers/**/*.h
)

add_executable(Editor ${EDITOR_SOURCES} 
                      ${EDITOR_HEADERS}
                      src/Main/Editor.cpp
)

target_link_libraries(Editor PRIVATE
    Engine
    imgui_lib
    glfw
    d3d11
    dxgi
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers
                                         ${CMAKE_CURRENT_SOURCE_DIR}/External
)

target_compile_definitions(Editor PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)