#include "application.h"

#include "shadow/application/game_loop.h"

namespace Shadow {

void Application::Init() {
    Log::Init();
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
}

}