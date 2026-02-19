file(GLOB_RECURSE TESTS_SOURCES
     src/*.cpp
)

add_library(UnitTests STATIC
    ${TESTS_SOURCES}
)