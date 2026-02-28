file(GLOB_RECURSE SCRIPT_SOURCES
    "${CMAKE_SOURCE_DIR}/Projects/*/Scripts/*.cpp"
)

message(STATUS "===== SCRIPTS FOUND =====")
foreach(file ${SCRIPT_SOURCES})
    message(STATUS ${file})
endforeach()
message(STATUS "=========================")



file(GLOB_RECURSE EDITOR_SOURCES
	src/**/*.cpp
)

file(GLOB_RECURSE EDITOR_HEADERS
	 Headers/**/*.hpp
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/Runtime/Shader"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Editor/Shader"
            "${CMAKE_BINARY_DIR}/Runtime/Shader"

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/Editor/Shader"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Editor/Shader"
            "${CMAKE_BINARY_DIR}/Editor/Shader"

    COMMENT "Copy Editor/Shader to Runtime and Editor directories"
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
                      ${SCRIPT_SOURCES}
)

target_link_libraries(Editor PRIVATE
    Game
    Engine
    glfw
    d3d11
    dxgi
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                         /Headers
                                         
)

target_include_directories(Editor PRIVATE
    ${CMAKE_SOURCE_DIR}/Projects
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