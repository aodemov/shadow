#include "game_loop.h"

#include "shadow/application/application.h"

namespace Shadow {

GameLoop::GameLoop()
    : mMaxFps(20),
      mLag(0),
      mInterval(0)
{
    SH_PROFILE_FUNCTION();

    mWindow = std::make_unique<Window>(WindowOptions("Shadow", 1000, 600, true));
    mEventBus = MakeScope<EventBus>();

#ifdef SH_DEBUGGER
    mDebugger = std::make_unique<Debugger>();
#endif

    mEventBus->AddListener<WindowCloseEvent>([&](WindowCloseEvent const &event) {
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

    mInterval = 1.0f / (float)mMaxFps;

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

    mLag += (float)mGameClock.GetDelta();

    while(mLag >= mInterval) {
        FixedUpdate(mInterval);
        mLag -= mInterval;
    }

    VariableUpdate((float)mGameClock.GetDelta());

#ifdef SH_DEBUGGER
    Debugger::Stats.ElapsedFrames++;
    Debugger::Stats.ElapsedTime += mGameClock.GetDelta();
    Debugger::Stats.FrameTime = (float)mGameClock.GetDelta();
#endif
}

void GameLoop::VariableUpdate(float delta) {
    SH_PROFILE_FUNCTION();

    mEventBus->ProcessAll();

    SceneManager::Instance().GetCurrentScene().VariableUpdate(delta);

#ifdef SH_DEBUGGER
    mDebugger->Update(delta);
#endif
    mWindow->Update();

#ifdef SH_DEBUGGER
    Debugger::Stats.VariableUpdateTime = delta;
#endif
}

void GameLoop::FixedUpdate(float delta) {
    SH_PROFILE_FUNCTION();

    SceneManager::Instance().GetCurrentScene().FixedUpdate(delta);

#ifdef SH_DEBUGGER
    Debugger::Stats.FixedUpdateTime = delta;
#endif
}

}
