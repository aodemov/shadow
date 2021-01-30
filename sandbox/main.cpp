#include <iostream>
#include <string>

#include "shadow/shadow.h"

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
        : camera(-5.0f, 5.0f, -5.0f, 5.0f),
          cameraPosition(0.0f),
          cameraSpeed(4.0f)
    {}

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
    }

    void VariableUpdate(double delta) override {
        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Render::Clear();

        camera.SetPosition(cameraPosition);
        camera.SetRotation(0.0f);

        Render::BeginScene(camera);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                Render::DrawRect({ 0.55f * i, 0.55f * j, 0.0f}, { 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f });
            }
        }

        Render::EndScene();
    }

private:

    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArray> va;
    Camera camera;

    glm::vec3 cameraPosition;
    float cameraSpeed;
};

int main() {
    Application::Init();

    SceneManager::Instance().Add("main", new MainScene);
    SceneManager::Instance().Load("main");

    Application::Run();

    Application::Quit();
}
