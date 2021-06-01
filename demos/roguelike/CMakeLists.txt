file(GLOB_RECURSE libsources *.h *.cpp *.hpp *.c *.cc)

add_executable(roguelike ${libsources})

target_link_libraries(roguelike PUBLIC shadow)

# Copy assets folder
add_custom_target(copy_assets_roguelike
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_BINARY_DIR}/bin/assets
        )
add_dependencies(roguelike copy_assets_roguelike)
