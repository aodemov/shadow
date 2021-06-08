#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
    explicit Window(const WindowOptions& options);
    ~Window();

    void Close();
    bool IsClosed() const;
    void Resize(int width, int height);
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void SetTitle(std::string const& title);
    std::string GetTitle() const;
    float GetAspectRatio() const;

    void Minimize();
    void Restore();
    void Maximize();

    bool IsMaximized() const;
    bool IsMinimized() const;

private:
    void Init();
    void Shutdown();
    void Update();

    GLFWwindow* mWindow;

    WindowOptions mOptions;

    friend class GameLoop;
    friend class Input;

#ifdef SH_DEBUGGER
    friend class Debugger;
#endif
};

}
