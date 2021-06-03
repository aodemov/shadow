#include <iostream>
#include <string>
#include <cmath>
#include "shadow/shadow.h"
#include <glm/gtx/closest_point.hpp>

#include "level.h"
#include "player.h"

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
    {
    }

    void Load() override {
        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

        On<WindowResizeEvent>([&](auto& e) {
            cameraController.Recalculate();
        });

        cameraController.SetPosition({ 0, 0, 0 });
        cameraController.SetRotation(0);
        cameraController.SetZoom(6);

        mLevel.Load();
        mPlayer.Load();

        On<KeyPressedEvent>([&](auto e) {
           if (e.GetKeyCode() == Key::R) {
               mLevel.Load();
           }
        });
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
        mPlayer.Update(delta);
        mLevel.Update(delta);

        Render::Clear();

        cameraController.SetPosition(mPlayer.GetPosition());

        Render::BeginScene(cameraController.GetCamera());

        mLevel.Draw();
        mPlayer.Draw();

        Render::EndScene();
    }

private:
    CameraController cameraController;

    Level mLevel;
    Player mPlayer;
};

int main() {
    Application::Init();

    Application::GetSceneManager().Add("main", new MainScene);
    Application::GetSceneManager().Show("main");

    Application::Run();

    Application::Quit();
}
