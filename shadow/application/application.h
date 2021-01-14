#pragma once

#include "shadow/events/event_bus.h"
#include "window.h"


namespace Shadow {
class Application {
public:
    Application();

    virtual ~Application() = default;

    virtual void Init();

    virtual void Run();

private:
    virtual void OnEvent(WindowResizeEvent const& event) {
        SH_INFO(event.ToString());
    }

    bool running = false;

    std::unique_ptr<Window> window;

    EventBus& eventBus;
};

}
