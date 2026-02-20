include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS_SOURCES 
    src/*.cpp
)

file(GLOB_RECURSE TESTS_HEADERS 
    Headers/*.hpp
)

add_executable(UnitTest
    ${TESTS_SOURCES} 
    ${TESTS_HEADERS}
)


target_link_libraries(UnitTest PRIVATE MathLib
                                       GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTest)