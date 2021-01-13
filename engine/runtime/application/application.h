#pragma once

#include <string>

#include "runtime/events/event_bus.h"

namespace Shadow {
class Application {
public:
    Application();

    virtual ~Application() = default;

    virtual void Init();

    virtual void Run();

private:
    EventBus eventBus;
};

}
