# === Lire le projet actif depuis LastProject.txt ===

set(LAST_PROJECT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LastProject.txt")

if(EXISTS ${LAST_PROJECT_FILE})
    file(READ ${LAST_PROJECT_FILE} ACTIVE_PROJECT_NAME)
    string(STRIP "${ACTIVE_PROJECT_NAME}" ACTIVE_PROJECT_NAME)
else()
    message(FATAL_ERROR "LastProject.txt not found in Editor folder")
endif()

configure_file(
    ${LAST_PROJECT_FILE}
    ${CMAKE_BINARY_DIR}/LastProject_copy.txt
    COPYONLY
)

# === Scripts du projet actif ===
set(PROJECT_SCRIPTS_PATH
    ${CMAKE_SOURCE_DIR}/Game/Projects/${ACTIVE_PROJECT_NAME}/Scripts
)

file(GLOB_RECURSE PROJECT_SCRIPT_SOURCES
    ${PROJECT_SCRIPTS_PATH}/**/*.cpp
)

file(GLOB_RECURSE PROJECT_SCRIPT_HEADERS
    ${PROJECT_SCRIPTS_PATH}/**/*.hpp
)

# === Sources Editor ===
file(GLOB_RECURSE EDITOR_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE EDITOR_CORE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers/**/*.hpp
)

# Fusion
set(EDITOR_SOURCES
    ${EDITOR_CORE_SOURCES}
    ${PROJECT_SCRIPT_SOURCES}
)

set(EDITOR_HEADERS
    ${EDITOR_CORE_HEADERS}
    ${PROJECT_SCRIPT_HEADERS}
)

message(STATUS "Active project: ${ACTIVE_PROJECT_NAME}")
message(STATUS "Scripts found: ${PROJECT_SCRIPT_SOURCES}")

# === HLSL Compilation (CSO dans Editor/Shader) ===

file(GLOB SHADERS
    ${CMAKE_SOURCE_DIR}/Editor/Shader/*.hlsl
)

foreach(SHADER ${SHADERS})

    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)

    set(OUTPUT_FILE
        ${CMAKE_SOURCE_DIR}/Editor/Shader/${SHADER_NAME}.cso
    )

    # Détection type selon nom
    if(SHADER_NAME MATCHES "VertexShader")
        set(SHADER_TYPE "vs_5_0")
    elseif(SHADER_NAME MATCHES "PixelShader")
        set(SHADER_TYPE "ps_5_0")
    else()
        message(FATAL_ERROR "Shader '${SHADER_NAME}' must contain VertexShader or PixelShader in name")
    endif()

    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND fxc
                /T ${SHADER_TYPE}
                /E main
                /Fo ${OUTPUT_FILE}
                ${SHADER}
        DEPENDS ${SHADER}
        COMMENT "Compiling ${SHADER_NAME}.hlsl -> ${SHADER_NAME}.cso"
        VERBATIM
    )

    list(APPEND SHADER_OUTPUTS ${OUTPUT_FILE})

endforeach()

add_custom_target(CompileShaders ALL
    DEPENDS ${SHADER_OUTPUTS}
)

# === Dupliquer dossier Shader (HLSL + CSO) vers build Runtime ===

add_custom_target(copy_runtime ALL
    DEPENDS CompileShaders
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/Runtime/Shader"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Editor/Shader"
            "${CMAKE_BINARY_DIR}/Runtime/Shader"

    COMMENT "Copy Shader folder (HLSL + CSO) to Runtime"
)

# === Dupliquer dossier Shader vers build Editor (debug) ===

add_custom_target(copy_editor ALL
    DEPENDS CompileShaders
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/Editor/Shader"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Editor/Shader"
            "${CMAKE_BINARY_DIR}/Editor/Shader"

    COMMENT "Copy Shader folder (HLSL + CSO) to build Editor"
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
    Game
    Engine
    glfw
    d3d11
    dxgi
    assimp
    DirectXTK
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
     ${PROJECT_SCRIPTS_PATH}
)

target_compile_definitions(Editor PRIVATE
    GLFW_EXPOSE_NATIVE_WIN32
)