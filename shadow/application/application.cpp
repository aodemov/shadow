#include "application.h"

#include "shadow/application/game_loop.h"

namespace Shadow {

void Application::Start() {
    GameLoop::Instance().Run();
}

void Application::Quit() {
    GameLoop::Instance().Stop();
}

}