file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_executable(snake ${libsources})

target_link_libraries(snake PUBLIC shadow)

# Copy assets folder
add_custom_target(copy_assets_snake
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_BINARY_DIR}/bin/assets
        )
add_dependencies(snake copy_assets_snake)
