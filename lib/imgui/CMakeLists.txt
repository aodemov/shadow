file(GLOB libsources
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/*.h
        )

add_library(imgui ${libsources})

target_include_directories(imgui PUBLIC imgui/)