#include <iostream>
#include <string>
#include <cmath>
#include "shadow/shadow.h"
#include <glm/gtx/closest_point.hpp>

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
    {
    }

    void Load() override {
        Render::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

        cameraController.SetPosition({ 0, 0, 0 });
        cameraController.SetRotation(0);
        cameraController.SetZoom(6);


    }

    void Show() override {
    }
    void Hide() override {
    }
    void Destroy() override {
    }

    void FixedUpdate(float delta) override {
        
    }

    void VariableUpdate(float delta) override {
        Render::Clear();
        Render::BeginScene(cameraController.GetCamera());

        Render::EndScene();
    }

private:
    CameraController cameraController;
};

int main() {
    Application::Init();

    Application::GetSceneManager().Add("main", new MainScene);
    Application::GetSceneManager().Show("main");

    Application::GetEventBus().AddListener<WindowCloseEvent>([](auto e) {
        Application::Stop();
    });

    Application::Run();

    Application::Quit();
}
