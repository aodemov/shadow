
# Fetch GTest Library
include(${PROJECT_SOURCE_DIR}/cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)

file(GLOB_RECURSE testfiles *.h *.cpp *.hpp *.c *.cc)

add_executable(
        unit_tests
        ${testfiles}
)

target_link_libraries(
        unit_tests
        gtest_main
        shadow
)