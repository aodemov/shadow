file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_executable(sandbox ${libsources})

target_link_libraries(sandbox PUBLIC shadow)

# Copy assets folder
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_BINARY_DIR}/bin/assets
        )
add_dependencies(sandbox copy_assets)