file(GLOB_RECURSE RUNTIME_SOURCES
	EngineBridge/src/*.cpp
    Shader/**/*.cso
  
)

file(GLOB_RECURSE RUNTIME_HEADERS
	EngineBridge/Headers/*.hpp
     Shader/**/*.hlsl
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/Runtime/Shader"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Shader" "${CMAKE_BINARY_DIR}/Runtime/Shader"
    COMMENT "Copy ${CMAKE_CURRENT_SOURCE_DIR}/Shader to ${CMAKE_BINARY_DIR}/Runtime/Shader"
)



add_executable(Runtime ${RUNTIME_SOURCES} 
                       ${RUNTIME_HEADERS}
                       ${SHADER_FILES}
                       EngineBridge/src/Main/main.cpp
                       
                       
)

target_include_directories(Runtime
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineBridge/Headers
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader
)


target_link_libraries(Runtime
    PRIVATE
        Engine
        glfw
        d3d11
        dxgi
)


