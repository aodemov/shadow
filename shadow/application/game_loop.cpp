#include "game_loop.h"

namespace Shadow {

GameLoop& GameLoop::Instance() {
    static GameLoop instance;
    return instance;
}


GameLoop::GameLoop()
    : eventBus(EventBus::Instance())
{
    maxFps = 20;
    window = std::make_unique<Window>(WindowOptions("Shadow", 1000, 600, false));
}

GameLoop::~GameLoop() {
}

void GameLoop::Run() {
    if (running)
        return;

    Init();
    while(running) {
        MainLoop();
    }
    Shutdown();
}

void GameLoop::Stop() {
    running = false;
}

void GameLoop::Init() {
    running = true;

    interval = 1.0 / maxFps;

    window->Init();
}

void GameLoop::Shutdown() {
    window->Shutdown();
}

void GameLoop::MainLoop() {
    Update();
    FixedUpdate(0.0);
}

void GameLoop::Update() {
    window->Update();
}

void GameLoop::FixedUpdate(float delta) {

}

}
