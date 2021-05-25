#include "game_loop.h"

#include "shadow/application/application.h"

namespace Shadow {

GameLoop& GameLoop::Instance() {
    static GameLoop instance;
    return instance;
}

Window& GameLoop::GetWindow() {
    return *(Instance().mWindow);
}


GameLoop::GameLoop()
    : mEventBus(EventBus::Instance())
{
    SH_PROFILE_FUNCTION();

    mMaxFps = 20;
    mWindow = std::make_unique<Window>(WindowOptions("Shadow", 1000, 600, true));
#ifdef SH_DEBUGGER
    mDebugger = std::make_unique<Debugger>();
#endif

    mEventBus.AddListener<WindowCloseEvent>([&](WindowCloseEvent const &event) {
        Application::Stop();
        Application::Quit();
    });
}

GameLoop::~GameLoop() {
    mGameClock.Pause();
}

void GameLoop::Run() {
    SH_PROFILE_FUNCTION();

    if (mRunning)
        return;

    mRunning = true;
    while(mRunning) {
        MainLoop();
    }
}

void GameLoop::Stop() {
    mRunning = false;
}

void GameLoop::Init() {
    SH_PROFILE_FUNCTION();

    mInterval = 1.0 / mMaxFps;

    mWindow->Init();

    Render::Init();

    mGameClock.Start();
#ifdef SH_DEBUGGER
    mDebugger->Init();
#endif

#ifdef SH_DEBUGGER
    Debugger::Stats.FixedFPS = mMaxFps;
#endif
}

void GameLoop::Shutdown() {
    SH_PROFILE_FUNCTION();

    Render::Shutdown();
    mWindow->Shutdown();
}

void GameLoop::MainLoop() {
    SH_PROFILE_FUNCTION();

    mGameClock.Update();

    mLag += mGameClock.GetDelta();

    while(mLag >= mInterval) {
        FixedUpdate(mInterval);
        mLag -= mInterval;
    }

    VariableUpdate(mGameClock.GetDelta());

#ifdef SH_DEBUGGER
    Debugger::Stats.ElapsedFrames++;
    Debugger::Stats.ElapsedTime += mGameClock.GetDelta();
    Debugger::Stats.FrameTime = mGameClock.GetDelta();
#endif
}

void GameLoop::VariableUpdate(double delta) {
    SH_PROFILE_FUNCTION();

    mEventBus.ProcessAll();

    SceneManager::Instance().GetCurrentScene().VariableUpdate(delta);

#ifdef SH_DEBUGGER
    mDebugger->Update((float)delta);
#endif
    mWindow->Update();

#ifdef SH_DEBUGGER
    Debugger::Stats.VariableUpdateTime = delta;
#endif
}

void GameLoop::FixedUpdate(double delta) {
    SH_PROFILE_FUNCTION();

    SceneManager::Instance().GetCurrentScene().FixedUpdate(delta);

#ifdef SH_DEBUGGER
    Debugger::Stats.FixedUpdateTime = delta;
#endif
}

}
