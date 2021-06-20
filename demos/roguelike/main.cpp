#include <iostream>
#include <string>
#include <cmath>
#include "shadow/shadow.h"
#include <glm/gtx/closest_point.hpp>

#include "level.h"
#include "player.h"

using namespace Shadow;

//class MainScene : public Scene {
//public:
//    MainScene()
//    {
//        mLevel = MakeRef<Level>();
//        mPlayer = MakeRef<Player>();
//        Add(mLevel);
//        Add(mPlayer);
//    }
//
//    void Load() override {
//        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
//
//        On<WindowResizeEvent>([&](auto& e) {
//            cameraController.Recalculate();
//        });
//
//        cameraController.SetPosition({ 0, 0, 0 });
//        cameraController.SetRotation(0);
//        cameraController.SetZoom(6);
//
//        On<KeyPressedEvent>([&](auto e) {
//           if (e.GetKeyCode() == Key::R) {
//               mLevel->OnLoad();
//           }
//        });
//
//        Scene::Load();
//    }
//
//    void VariableUpdate(float delta) override {
//        Render::Clear();
//
//        cameraController.SetPosition(mPlayer->GetPosition());
//
//        Render::BeginScene(cameraController.GetCamera());
//
//        Scene::VariableUpdate(delta);
//
//        Render::EndScene();
//    }
//
//private:
//    CameraController cameraController;
//
//    Ref<Level> mLevel;
//    Ref<Player> mPlayer;
//};

int main() {
    Application::Init();

    auto mainScene = new Scene();


    auto player = mainScene->Create();
    player.AddComponent<ScriptComponent>().Bind<Player>();

    auto level = mainScene->Create();
    level.AddComponent<ScriptComponent>().Bind<Level>();

    Application::GetSceneManager().Add("main", mainScene);
    Application::GetSceneManager().Show("main");

    Application::Run();

    Application::Quit();
}
