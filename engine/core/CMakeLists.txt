file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_library(core ${libsources})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(core PUBLIC spdlog glfw glad)