file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_library(shadow ${libsources} shpch.cpp shpch.h)

target_link_libraries(shadow PUBLIC spdlog glfw glad glm imgui stb_image stb_truetype)

target_include_directories(shadow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_precompiled_header(shadow shpch.h SOURCE_CXX shpch.cpp FORCEINCLUDE)