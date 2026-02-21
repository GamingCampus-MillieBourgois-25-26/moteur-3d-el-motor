

file(GLOB_RECURSE EDITOR_SOURCES
	src/**/*.cpp
)

file(GLOB_RECURSE EDITOR_HEADERS
	 Headers/**/*.hpp
)



list(APPEND EDITOR_SOURCES
    External/imgui/src/CoreSources/imgui.cpp
    External/imgui/src/CoreSources/imgui_draw.cpp
    External/imgui/src/CoreSources/imgui_widgets.cpp
    External/imgui/src/CoreSources/imgui_tables.cpp
    External/imgui/src/CoreSources/imgui_demo.cpp
    External/imgui/src/Backend/imgui_impl_dx11.cpp
    External/imgui/src/Backend/imgui_impl_glfw.cpp
    External/ImGuiFileLog/src/ImGuiFileDialog.cpp
)

add_executable(Editor ${EDITOR_SOURCES} 
                      ${EDITOR_HEADERS}
)

target_link_libraries(Editor PRIVATE
    Engine
    glfw
    d3d11
    dxgi
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                         /Headers
)


target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers
     External/imgui/includes/CoreIncludes
     External/imgui/includes/backend
     External/imgui/src/Backend   
     External/ImGuiFileLog/includes/coreIncludes
     External/ImGuiFileLog/includes/dirent
     External/Json
)

target_compile_definitions(Editor PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)