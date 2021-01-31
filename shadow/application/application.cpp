#include "application.h"

#include "shadow/application/game_loop.h"
#include "shadow/core/debug/profiling.h"

namespace Shadow {

void Application::Init() {
    Log::Init();
    SH_PROFILE_INIT("profile-data.json");
    GameLoop::Instance().Init();
}

void Application::Run() {
    GameLoop::Instance().Run();
}

void Application::Stop() {
    GameLoop::Instance().Stop();
}

void Application::Quit() {
    GameLoop::Instance().Shutdown();
    SH_PROFILE_SHUTDOWN();
}

}