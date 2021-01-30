#include "game_loop.h"

#include "shadow/application/application.h"

namespace Shadow {

GameLoop& GameLoop::Instance() {
    static GameLoop instance;
    return instance;
}

Window& GameLoop::GetWindow() {
    return *(Instance().window);
}


GameLoop::GameLoop()
    : eventBus(EventBus::Instance())
{
    maxFps = 20;
    window = std::make_unique<Window>(WindowOptions("Shadow", 1000, 600, false));

    eventBus.addListener<WindowCloseEvent>([&](WindowCloseEvent const& event){
        Application::Stop();
        Application::Quit();
    });
}

GameLoop::~GameLoop() {
    gameClock.Pause();
}

void GameLoop::Run() {
    if (running)
        return;

    running = true;
    while(running) {
        MainLoop();
    }
}

void GameLoop::Stop() {
    running = false;
}

void GameLoop::Init() {
    interval = 1.0 / maxFps;

    window->Init();

    gameClock.Start();
}

void GameLoop::Shutdown() {
    window->Shutdown();
}

void GameLoop::MainLoop() {
    gameClock.Update();

    lag += gameClock.GetDelta();

    while(lag >= interval) {
        FixedUpdate(interval);
        lag -= interval;
    }

    VariableUpdate(gameClock.GetDelta());
}

void GameLoop::VariableUpdate(double delta) {
    eventBus.processAll();

    SceneManager::Instance().GetCurrentScene().VariableUpdate(delta);

    window->Update();
}

void GameLoop::FixedUpdate(double delta) {
    SceneManager::Instance().GetCurrentScene().FixedUpdate(delta);
}

}
