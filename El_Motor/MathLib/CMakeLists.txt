file(GLOB_RECURSE MATHS_SOURCES
     src/*.cpp
     src/*.inl
)

file(GLOB_RECURSE MATHS_HEADERS
     Headers/*.hpp
)

add_library(MathLib STATIC
    ${MATHS_SOURCES}
    ${MATHS_HEADERS}
)

target_include_directories(MathLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers 
)