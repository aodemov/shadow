#include "application.h"

#include "shadow/core/debug/profiling.h"

namespace Shadow {

void Application::Init() {
    Log::Init();
    SH_PROFILE_INIT("profile-data.json");
    mGameLoop = MakeScope<GameLoop>();
    mGameLoop->Init();
}

void Application::Run() {
    mGameLoop->Run();
}

void Application::Stop() {
    mGameLoop->Stop();
}

void Application::Quit() {
    mGameLoop->Shutdown();
    SH_PROFILE_SHUTDOWN();
}

}