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
    SH_PROFILE_FUNCTION();

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
    SH_PROFILE_FUNCTION();

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
    SH_PROFILE_FUNCTION();

    interval = 1.0 / maxFps;

    window->Init();

    Render::Init();

    gameClock.Start();
}

void GameLoop::Shutdown() {
    SH_PROFILE_FUNCTION();

    Render::Shutdown();
    window->Shutdown();
}

void GameLoop::MainLoop() {
    SH_PROFILE_FUNCTION();

    gameClock.Update();

    lag += gameClock.GetDelta();

    while(lag >= interval) {
        FixedUpdate(interval);
        lag -= interval;
    }

    VariableUpdate(gameClock.GetDelta());
}

void GameLoop::VariableUpdate(double delta) {
    SH_PROFILE_FUNCTION();

    eventBus.processAll();

    SceneManager::Instance().GetCurrentScene().VariableUpdate(delta);

    window->Update();
}

void GameLoop::FixedUpdate(double delta) {
    SH_PROFILE_FUNCTION();

    SceneManager::Instance().GetCurrentScene().FixedUpdate(delta);
}

}
