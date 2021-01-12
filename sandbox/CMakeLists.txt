file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_executable(sandbox ${libsources})

target_link_libraries(sandbox PUBLIC runtime)