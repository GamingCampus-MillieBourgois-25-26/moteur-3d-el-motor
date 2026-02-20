file(GLOB_RECURSE MATHS_SOURCES
     src/*.cpp
)

file(GLOB_RECURSE MATHS_HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.inl
)

add_library(MathLib STATIC
    ${MATHS_SOURCES}
    ${MATHS_HEADERS}
)

target_include_directories(MathLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)