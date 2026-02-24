file(GLOB_RECURSE GAME_SOURCES
src/**/*.cpp
  
)

file(GLOB_RECURSE GAME_HEADERS
includes/**/*.hpp
)


add_library(Game
    ${GAME_SOURCES}
    ${GAME_HEADERS}
)

target_include_directories(Game
    PUBLIC
    #${CMAKE_CURRENT_SOURCE_DIR}/includes
)


target_link_libraries(Game
    PRIVATE
        Engine
        glfw
        d3d11
        dxgi
)