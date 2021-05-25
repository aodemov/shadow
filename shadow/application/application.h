#pragma once

#include "shadow/events/event_bus.h"
#include "shadow/application/game_loop.h"
#include "window.h"


namespace Shadow {

class Application {
public:
    static void Init();
    static void Run();
    static void Stop();
    static void Quit();

    static const GameLoop& GetGameLoop() { return *mGameLoop.get(); }
    static const Window& GetWindow() { return *mGameLoop->mWindow.get(); }
    static EventBus& GetEventBus() { return *mGameLoop->mEventBus.get(); }
    static SceneManager& GetSceneManager() { return *mGameLoop->mSceneManager.get(); }

private:
    static inline Scope<GameLoop> mGameLoop;
};

}
