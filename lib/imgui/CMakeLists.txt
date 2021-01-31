file(GLOB libsources
        imgui.cpp
        imgui_draw.cpp
        imgui_demo.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        *.h
        )

add_library(imgui ${libsources})

target_include_directories(imgui PUBLIC /)