#include <iostream>
#include <string>

#include "shadow/shadow.h"

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
    {
        SH_CORE_INFO("Scene constructor");
    }

    ~MainScene() override {
        SH_CORE_INFO("Scene destructor");
    }

    void Load() override {
        SH_INFO("Scene load");

        auto tex = MakeRef<Texture>("assets/textures/test.png");
        sprite1 = MakeScope<Sprite>(tex, glm::vec3{5, 5, 1}, glm::vec2{1, 1}, 45);
        sprite10 = MakeScope<Sprite>(tex, glm::vec3{0, 6, 1}, glm::vec2{1, 1}, 45);
        sprite11 = MakeScope<Sprite>(tex, glm::vec3{2, 6, 1}, glm::vec2{1, 1}, 45);
        sprite2 = MakeScope<Sprite>(MakeRef<Texture>("assets/textures/test2.png"), glm::vec3{7, 1, 1}, glm::vec2{7.2, 5});

        auto tilemap = MakeRef<Texture>("assets/textures/tilemap.png");
        tile1 = MakeScope<Sprite>(MakeRef<SubTexture>(tilemap, glm::vec2{16, 16},glm::vec2{3 * 16, 1 * 16}),
                                  glm::vec3{0, 0, 1.0f});

        tile2 = MakeScope<Sprite>(MakeRef<SubTexture>(tilemap, glm::vec2{2 * 16, 2 * 16},glm::vec2{6 * 16, 3 * 16}),
                                  glm::vec3{1.5f, 0, 1.0f}, glm::vec2{ 2, 2 });

        font1 = MakeRef<Font>("assets/fonts/comic.ttf", 100);
    }

    void Show() override {
        SH_INFO("Scene show");
    }

    void Hide() override {
        SH_INFO("Scene hide");
    }
    void Destroy() override {
        SH_INFO("Scene unload");
    }

    void FixedUpdate(float delta) override {
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

    void VariableUpdate(float delta) override {
        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Render::Clear();

        cameraController.SetPosition(cameraPosition);
        cameraController.SetRotation(cameraRotation);
        cameraController.SetZoom(cameraZoom);


        Render::BeginScene(cameraController.GetCamera());

        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
                Render::DrawRect({ x, y + 7, 0.0f }, { 0.45f, 0.45f }, color);
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

        Render::DrawRect({ -3, 0, 0.5f }, { 2.0f * 40 / Application::GetWindow().GetHeight(), 2.0f * 40 / Application::GetWindow().GetHeight() }, { 1.0f, 1.0f, 0.0f, 1.0f });

        Render::DrawText("The quick brown fox jumps over the lazy dog", { 0, 1.2f, 1.0f }, font1, glm::vec4{1.0f});

        Render::EndScene();
    }

private:
    CameraController cameraController;

    glm::vec3 cameraPosition{0.0f};
    float cameraSpeed{8.0f};
    float cameraZoom{1.0f};
    float cameraRotation{0.0f};

    Scope<Sprite> sprite1;
    Scope<Sprite> sprite10;
    Scope<Sprite> sprite11;
    Scope<Sprite> sprite2;
    Scope<Sprite> tile1;
    Scope<Sprite> tile2;
    Ref<Font> font1;
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
