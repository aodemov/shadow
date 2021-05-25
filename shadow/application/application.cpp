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
    SH_CORE_INFO("Application stop");
    mGameLoop->Stop();
}

void Application::Quit() {
    SH_CORE_INFO("Application quit");
    mGameLoop->Shutdown();
    SH_PROFILE_SHUTDOWN();
}

}