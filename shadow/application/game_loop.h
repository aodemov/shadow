#pragma once

#include "shadow/events/event_bus.h"
#include "shadow/application/window.h"
#include "shadow/core/time/clock.h"

namespace Shadow {

class GameLoop {
public:
    static GameLoop &Instance();

private:
    GameLoop();

    ~GameLoop();

    void Run();
    void Stop();

    void MainLoop();

    void Init();
    void FixedUpdate(double delta);
    void VariableUpdate(double delta);
    void Shutdown();

    bool running = false;

    int maxFps;
    double interval;
    double lag;
    Clock gameClock;

    std::unique_ptr<Window> window;
    EventBus& eventBus;

    friend class Application;
};

}
