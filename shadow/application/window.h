#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shadow/events/event_bus.h"

#include "shadow/events/application_events.h"
#include "shadow/events/mouse_events.h"
#include "shadow/events/keyboard_events.h"

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

    void Close();
    bool IsClosed() const;
    void Resize(unsigned int width, unsigned int height);
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void SetTitle(std::string const& title);
    std::string GetTitle() const;

    void Minimize();
    void Restore();
    void Maximize();

    bool IsMaximized() const;
    bool IsMinimized() const;

private:
    void Init();
    void Shutdown();

    GLFWwindow* window;

    WindowOptions options;
    EventBus& eventBus;
};

}
