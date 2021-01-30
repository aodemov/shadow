#pragma once

#include "shadow/events/event_bus.h"
#include "shadow/application/window.h"
#include "shadow/core/time/clock.h"
#include "shadow/scene/scene_manager.h"

#include "shadow/renderer/shader.h"
#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/render.h"

namespace Shadow {

class GameLoop {
public:
    static GameLoop &Instance();

    static Window& GetWindow();

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
