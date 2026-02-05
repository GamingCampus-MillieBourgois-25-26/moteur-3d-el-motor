file(GLOB_RECURSE ENGINE_SOURCES
    *.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    include/*.hpp
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_sources(Engine PRIVATE Engine.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)