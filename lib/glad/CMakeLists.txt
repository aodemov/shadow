add_library(glad
        glad/include/glad/gl.h
        glad/include/KHR/khrplatform.h
        glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include/)