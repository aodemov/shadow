#pragma once

#include "shadow/events/event_bus.h"
#include "window.h"


namespace Shadow {

class Application {
public:
    static void Init();
    static void Run();
    static void Stop();
    static void Quit();
};

}
