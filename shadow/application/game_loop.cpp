#include "game_loop.h"

#include "shadow/application/application.h"
#include "shadow/core/math/random.h"

namespace Shadow {

GameLoop::GameLoop()
    : mMaxFps(60),
      mLag(0),
      mInterval(0)
{
    SH_PROFILE_FUNCTION();

    mEventQueue = MakeScope<EventQueue>();
    mWindow = MakeScope<Window>(WindowOptions("Shadow", 1000, 600, true));
    mSceneManager = MakeScope<SceneManager>();

#ifdef SH_DEBUGGER
    mDebugger = std::make_unique<Debugger>();
#endif
}

GameLoop::~GameLoop() {
    mGameClock.Pause();
}

void GameLoop::Run() {
    SH_PROFILE_FUNCTION();

    if (mRunning)
        return;

    mRunning = true;
    mStopped = false;
    while(mRunning) {
        MainLoop();
    }

    mStopped = true;

    if (mShouldQuit)
        Shutdown();
}

void GameLoop::Stop() {
    mRunning = false;
}

void GameLoop::Init() {
    SH_PROFILE_FUNCTION();

    mInterval = 1.0f / (float)mMaxFps;

    mWindow->Init();

    Render::Init();
    Random::Init();

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

    if (!mStopped) {
        mShouldQuit = true;
        if (mRunning) {
            Stop();
        }

        return;
    }

    mSceneManager->Shutdown();

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

    while (mEventQueue->HasPending()) {
        const auto& event = mEventQueue->Front();
        mSceneManager->CurrentScene().mEventBus.Emit(event);

#ifdef SH_DEBUGGER
        mDebugger->mEventBus.Emit(event);
#endif

        mEventQueue->Pop();

    }

    mSceneManager->CurrentScene().VariableUpdate(delta);

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

    mSceneManager->CurrentScene().FixedUpdate(delta);

#ifdef SH_DEBUGGER
    Debugger::Stats.FixedUpdateTime = delta;
#endif
}

}
