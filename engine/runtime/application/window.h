#pragma once

#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Shadow {

struct WindowOptions {
    std::string Title;
    uint32_t Width;
    uint32_t Height;
    bool VSync;

    explicit WindowOptions(const std::string& title = "Shadow",
                  uint32_t width = 800,
                  uint32_t height = 600, bool vsync = false)
            : Title(title), Width(width), Height(height), VSync(vsync) {}
};

class Window {
public:
    explicit Window(WindowOptions options);
    ~Window();

    void OnUpdate();

private:
    void Init();
    void Shutdown();

    GLFWwindow* window;

    WindowOptions options;
};

}
