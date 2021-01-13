#pragma once

#include <string>
#include <memory>

#include "runtime/events/event_bus.h"
#include "runtime/application/window.h"


namespace Shadow {
class Application {
public:
    Application();

    virtual ~Application() = default;

    virtual void Init();

    virtual void Run();

private:
    bool running = false;

    std::unique_ptr<Window> window;

    EventBus& eventBus;
};

}
