#include <iostream>
#include <string>

#include "shadow/shadow.h"

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
        : cameraPosition(0.0f),
          cameraSpeed(8.0f),
          cameraZoom(1.0f),
          cameraRotation(0.0f)
    {
        auto tex = MakeRef<Texture>("assets/textures/test.png");
        sprite1 = MakeScope<Sprite>(tex, glm::vec3{5, 5, 1}, glm::vec2{1, 1}, 45);
        sprite10 = MakeScope<Sprite>(tex, glm::vec3{0, 6, 1}, glm::vec2{1, 1}, 45);
        sprite11 = MakeScope<Sprite>(tex, glm::vec3{2, 6, 1}, glm::vec2{1, 1}, 45);
        sprite2 = MakeScope<Sprite>(MakeRef<Texture>("assets/textures/test2.png"), glm::vec3{7, 1, 1}, glm::vec2{7.2, 5});

        auto tilemap = MakeRef<Texture>("assets/textures/tilemap.png");
        tile1 = MakeScope<Sprite>(MakeRef<SubTexture>(tilemap, glm::vec2{16, 16},glm::vec2{3 * 16, 1 * 16}),
                                         glm::vec3{-2, -2, 1.0f});

        tile2 = MakeScope<Sprite>(MakeRef<SubTexture>(tilemap, glm::vec2{2 * 16, 2 * 16},glm::vec2{6 * 16, 3 * 16}),
                                         glm::vec3{0, -2, 1.0f}, glm::vec2{ 2, 2 });
    }

    void Create() override {

    }

    void Start() override {
        SH_INFO("Scene start");
    }

    void Shutdown() override {
        SH_INFO("Scene shutdown");
    }
    void Destroy() override {
        SH_INFO("Scene destroy");
    }

    void FixedUpdate(double delta) override {
        if (Input::IsKeyPressed(Key::W)) {
            cameraPosition.y += cameraSpeed * delta;
        }
        if (Input::IsKeyPressed(Key::A)) {
            cameraPosition.x -= cameraSpeed * delta;
        }
        if (Input::IsKeyPressed(Key::S)) {
            cameraPosition.y -= cameraSpeed * delta;
        }
        if (Input::IsKeyPressed(Key::D)) {
            cameraPosition.x += cameraSpeed * delta;
        }
        if (Input::IsKeyPressed(Key::Q)) {
            cameraRotation -= 20.0f;
        }
        if (Input::IsKeyPressed(Key::E)) {
            cameraRotation += 20.0f;
        }
        if (Input::IsKeyPressed(Key::X)) {
            cameraZoom += 0.4f;
        }
        if (Input::IsKeyPressed(Key::Z)) {
            cameraZoom -= 0.4f;
        }
    }

    void VariableUpdate(double delta) override {
        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Render::Clear();

        cameraController.SetPosition(cameraPosition);
        cameraController.SetRotation(cameraRotation);
        cameraController.SetZoom(cameraZoom);


        Render::BeginScene(cameraController.GetCamera());

//        Render::TestLine();


        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                Render::DrawRect({ 0.55f * i, 0.55f * j, 0.0f}, { 0.5f, 0.5f },
                                 {
                                i % 2 ? 1.0f : 0.0f,
                                   i % 3 ? 1.0f : 0.0f,
                                   j % 2 ? 1.0f : 0.0f , 1.0f },
                                   i == 5 && j == 5 ? 45.0f : 0.0f);
            }
        }

        Render::DrawRect({2.5, 2.5, 0.8}, {2.35, 2.5}, {0.0f, 0.0f, 1.0f, 0.5f});

        static float rot = 0.0f;
        rot += delta * 100.0f;

        sprite1->Draw();
        sprite10->Draw();
        sprite11->Draw();
        sprite1->SetRotation(rot);
        sprite2->Draw();

        tile1->Draw();
        tile2->Draw();

        Render::EndScene();
    }

private:
    CameraController cameraController;

    glm::vec3 cameraPosition;
    float cameraSpeed;
    float cameraZoom;
    float cameraRotation;

    Scope<Sprite> sprite1;
    Scope<Sprite> sprite10;
    Scope<Sprite> sprite11;
    Scope<Sprite> sprite2;
    Scope<Sprite> tile1;
    Scope<Sprite> tile2;
};

int main() {
    Application::Init();

    SceneManager::Instance().Add("main", new MainScene);
    SceneManager::Instance().Load("main");

    Application::Run();

    Application::Quit();
}
