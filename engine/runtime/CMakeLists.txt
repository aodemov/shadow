file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_library(runtime ${libsources})

target_link_libraries(runtime PUBLIC core)

target_include_directories(runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)