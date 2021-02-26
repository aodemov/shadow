file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_executable(snake ${libsources})

target_link_libraries(snake PUBLIC shadow)