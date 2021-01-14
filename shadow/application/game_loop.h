#pragma once

#include "shadow/events/event_bus.h"
#include "shadow/application/window.h"

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
    void FixedUpdate(float delta);
    void Update();
    void Shutdown();

    bool running = false;

    int maxFps;
    float interval;

    std::unique_ptr<Window> window;
    EventBus& eventBus;

    friend class Application;
};

}
