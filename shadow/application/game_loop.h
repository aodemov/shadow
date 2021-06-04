#pragma once

#include "shadow/events/event_queue.h"
#include "shadow/application/window.h"
#include "shadow/core/time/clock.h"
#include "shadow/ecs/scene_manager.h"

#include "shadow/renderer/shader.h"
#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/render.h"

#include "shadow/core/debug/debugger.h"

namespace Shadow {

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

private:

    void Run();
    void Stop();

    void MainLoop();

    void Init();
    void FixedUpdate(float delta);
    void VariableUpdate(float delta);
    void Shutdown();

    bool mRunning = false;
    bool mStopped = true;
    bool mShouldQuit = false;

    int mMaxFps;
    float mInterval;
    float mLag;
    Clock mGameClock;

    Scope<Window> mWindow;
    Scope<SceneManager> mSceneManager;
    Scope<EventQueue> mEventQueue;

#ifdef SH_DEBUGGER
    Scope<Debugger> mDebugger;
#endif

    friend class Application;
};

}
