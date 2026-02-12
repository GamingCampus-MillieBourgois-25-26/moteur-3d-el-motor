file(GLOB_RECURSE RUNTIME_SOURCES
	EngineBridge/src/*.cpp
  
)

file(GLOB_RECURSE RUNTIME_HEADERS
	EngineBridge/Headers/*.hpp 
)

file(GLOB SHADER_FILES
    #Shaders/*.hlsl
)



add_executable(Runtime ${RUNTIME_SOURCES} 
                       ${RUNTIME_HEADERS}
                       ${SHADER_FILES}
                       EngineBridge/src/Main/main.cpp
                       
)

target_include_directories(Runtime
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineBridge/Headers
)


target_link_libraries(Runtime
    PRIVATE
        Engine
        glfw
        d3d11
        dxgi
)


