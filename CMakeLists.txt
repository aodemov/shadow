cmake_minimum_required(VERSION 3.17)
project(Shadow)

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output paths
message(STATUS "Project binary dir: ${PROJECT_BINARY_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set compiler specific stuff
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS=1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj /W3")
endif()
if (MINGW)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    endif()
endif()
#if (UNIX)
#    add_definitions(--no-pie)
#endif()

# Cmake Precompiled Headers
include(cmake/precompiled-headers.cmake)

add_subdirectory(lib)
add_subdirectory(shadow)
add_subdirectory(sandbox)
add_subdirectory(demos/snake)
add_subdirectory(demos/roguelike)
#add_subdirectory(demos/platformer)

# Tests

enable_testing()

add_subdirectory(tests)