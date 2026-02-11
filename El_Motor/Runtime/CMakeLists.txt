file(GLOB_RECURSE RUNTIME_SOURCES
	EngineBridge/src/*.cpp

    
)

file(GLOB_RECURSE RUNTIME_HEADERS
	Headers/*.hpp
    
)




add_executable(Runtime ${RUNTIME_SOURCES} 
                       ${RUNTIME_HEADERS} 
                       
)

target_include_directories(Runtime
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineBridge/Header
)


target_link_libraries(Runtime
    PRIVATE
        Engine
        glfw
        d3d11
        dxgi
)


