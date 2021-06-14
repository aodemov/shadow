#include <iostream>
#include <string>

#include "shadow/shadow.h"

#include "progress_bar.h"
#include "camera_script.h"

using namespace Shadow;

//class MainScene : public Scene {
//public:
//    MainScene()
//    {
//        SH_CORE_INFO("Scene constructor");
//    }
//
//    ~MainScene() override {
//        SH_CORE_INFO("Scene destructor");
//    }
//
//    void Load() override {
//        SH_INFO("Scene load");
//        On<WindowResizeEvent>([&](auto& e) {
//            cameraController.Recalculate();
//        });
//
//        auto tex = MakeRef<Texture>("assets/textures/test.png");
//        sprite1 = MakeScope<Sprite>(tex, glm::vec3{5, 5, 1}, glm::vec2{1, 1}, 45);
//        sprite10 = MakeScope<Sprite>(tex, glm::vec3{0, 6, 1}, glm::vec2{1, 1}, 45);
//        sprite11 = MakeScope<Sprite>(tex, glm::vec3{2, 6, 1}, glm::vec2{1, 1}, 45);
//        sprite2 = MakeScope<Sprite>(MakeRef<Texture>("assets/textures/test2.png"), glm::vec3{7, 1, 1}, glm::vec2{7.2, 5});
//
//        auto tilemap = MakeRef<Texture>("assets/textures/tilemap.png");
//        tile1 = MakeScope<Sprite>(SubTexture(tilemap, glm::vec2{3 * 16, 1 * 16}, glm::vec2{16, 16}),
//                                  glm::vec3{0, 0, 1.0f});
//
//        tile2 = MakeScope<Sprite>(SubTexture(tilemap, glm::vec2{6 * 16, 3 * 16}, glm::vec2{2 * 16, 2 * 16}),
//                                  glm::vec3{1.5f, 0, 1.0f}, glm::vec2{ 2, 2 });
//
//        font1 = MakeRef<Font>("assets/fonts/comic.ttf", 50);
//
//        bar = MakeRef<ProgressBar>(MakeRef<Font>("assets/fonts/arial.ttf", 25));
//        bar->Width(50, true).Height(30).CenterX().MarginBottom(5, true);
//        UI::Add(std::dynamic_pointer_cast<UiBlock, ProgressBar>(bar));
//
//
//        Animation animation(tilemap, 1.5f, {
//                { { 8  * 16, 5 * 16 }, { 16, 32 } },
//                { { 9  * 16, 5 * 16 }, { 16, 32 } },
//                { { 10 * 16, 5 * 16 }, { 16, 32 } },
//                { { 11 * 16, 5 * 16 }, { 16, 32 } },
//                { { 12 * 16, 5 * 16 }, { 16, 32 } },
//                { { 13 * 16, 5 * 16 }, { 16, 32 } },
//                { { 14 * 16, 5 * 16 }, { 16, 32 } },
//                { { 15 * 16, 5 * 16 }, { 16, 32 } },
//        });
//
//        AnimationController animationController({
//            { "default", animation }
//        }, "default");
//
//        animatedSprite = MakeScope<AnimatedSprite>(animationController, glm::vec3{ -1, -1, 1.0f }, glm::vec2{ 1, 2 });
//    }
//
//    void OnEnable() override {
//        SH_INFO("Scene show");
//    }
//
//    void OnDisable() override {
//        SH_INFO("Scene hide");
//    }
//    void Destroy() override {
//        SH_INFO("Scene unload");
//    }
//
//    void FixedUpdate(float delta) override {
//        if (Input::IsKeyPressed(Key::W)) {
//            cameraPosition.y += cameraSpeed * delta;
//        }
//        if (Input::IsKeyPressed(Key::A)) {
//            cameraPosition.x -= cameraSpeed * delta;
//        }
//        if (Input::IsKeyPressed(Key::S)) {
//            cameraPosition.y -= cameraSpeed * delta;
//        }
//        if (Input::IsKeyPressed(Key::D)) {
//            cameraPosition.x += cameraSpeed * delta;
//        }
//        if (Input::IsKeyPressed(Key::Q)) {
//            cameraRotation -= 20.0f;
//        }
//        if (Input::IsKeyPressed(Key::E)) {
//            cameraRotation += 20.0f;
//        }
//        if (Input::IsKeyPressed(Key::X)) {
//            cameraZoom += 0.4f;
//        }
//        if (Input::IsKeyPressed(Key::Z)) {
//            cameraZoom -= 0.4f;
//        }
//    }
//
//    void VariableUpdate(float delta) override {
//        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
//        Render::Clear();
//
//        cameraController.SetPosition(cameraPosition);
//        cameraController.SetRotation(cameraRotation);
//        cameraController.SetZoom(cameraZoom);
//
//        animatedSprite->Update(delta);
//
//
//        Render::BeginScene(cameraController.GetCamera());
//
//        for (float y = -5.0f; y < 5.0f; y += 0.5f)
//        {
//            for (float x = -5.0f; x < 5.0f; x += 0.5f)
//            {
//                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
//                Render::DrawRect({ x, y + 7, 0.0f }, { 0.45f, 0.45f }, color);
//            }
//        }
//
//
//        Render::DrawRect({2.5, 2.5, 0.8}, {2.35, 2.5}, {0.0f, 0.0f, 1.0f, 0.5f});
//
//        static float rot = 0.0f;
//        rot += delta * 100.0f;
//
//        sprite1->Draw();
//        sprite10->Draw();
//        sprite11->Draw();
//        sprite1->Rotation() = rot;
//        sprite2->Draw();
//
//        tile1->Draw();
//        tile2->Draw();
//
//        bar->SetValue(fmod(rot, 100.0f));
//
//        animatedSprite->Draw();
//
//        Render::DrawRect({ -3, 0, 0.5f }, { 2.0f * 40 / Application::GetWindow().GetHeight(), 2.0f * 40 / Application::GetWindow().GetHeight() }, { 1.0f, 1.0f, 0.0f, 1.0f });
//
//        Render::DrawText("The quick brown fox jumps over the lazy dog", { 0, 1.2f, 1.0f }, font1, glm::vec4{1,0,1, 0.5f});
//
//        Render::EndScene();
//
//        UI::Begin();
//        float w = Application::GetWindow().GetWidth();
//        float h = Application::GetWindow().GetHeight();
//
//
//
////        UiBlock b1;
////        b1.MarginLeft(20).MarginTop(20).MarginBottom(20).Width(25, true);
////        b1.Calculate(w, h);
////        b1.Draw();
////
////        Label l1("The quick brown fox jumps over the lazy dog", { w / 2, 100 }, font1, { 1, 0, 1, 0.5f });
////        l1.Draw();
////        Render::DrawText("The quick brown fox jumps over the lazy dog", { (w - tw) / 2, 100, 1.0f }, font1, glm::vec4{1,0,1, 0.5f});
//
////        UIBlock b2;
////        b2.MarginTop(10, true).MarginRight(20).Width(300).Height(200);
////        b2.Calculate(w, h);
////        b2.Draw();
////
////        UIBlock b3;
////        b3.MarginBottom(0).Width(50, true).Height(30).CenterX();
////        b3.Calculate(w, h);
////        b3.Draw();
////
////        UIBlock b4;
////        b4.MarginLeft(100).MarginBottom(50, true).Width(50).Height(50).CenterBoth();
////        b4.Calculate(w, h);
////        b4.Draw();
//
//        UI::End();
//    }
//
//private:
//    CameraController cameraController;
//
//    glm::vec3 cameraPosition{0.0f};
//    float cameraSpeed{8.0f};
//    float cameraZoom{1.0f};
//    float cameraRotation{0.0f};
//
//    Scope<Sprite> sprite1;
//    Scope<Sprite> sprite10;
//    Scope<Sprite> sprite11;
//    Scope<Sprite> sprite2;
//    Scope<Sprite> tile1;
//    Scope<Sprite> tile2;
//    Ref<Font> font1;
//
//    Scope<AnimatedSprite> animatedSprite;
//
//    Ref<ProgressBar> bar;
//};


int main() {
    Application::Init();

    auto mainScene = new Scene();


    auto& cam = mainScene->Create();

    CameraController cameraController;
    cam.AddComponent<CameraComponent>(cameraController);
    cam.AddComponent<ScriptComponent>().Bind<CameraScript>();
    mainScene->SetCamera(&cam.GetComponent<CameraComponent>().cameraController.GetCamera());


    auto tex = MakeRef<Texture>("assets/textures/test.png");
    Sprite sprite(tex);

    auto& rect = mainScene->Create();

    rect.AddComponent<Transform>(glm::vec2{5, 5}, 45, glm::vec2{1, 1});
    rect.AddComponent<SpriteComponent>(sprite);


    auto tilemap = MakeRef<Texture>("assets/textures/tilemap.png");
    Animation animation(tilemap, 1.5f, {
        { { 8  * 16, 5 * 16 }, { 16, 32 } },
        { { 9  * 16, 5 * 16 }, { 16, 32 } },
        { { 10 * 16, 5 * 16 }, { 16, 32 } },
        { { 11 * 16, 5 * 16 }, { 16, 32 } },
        { { 12 * 16, 5 * 16 }, { 16, 32 } },
        { { 13 * 16, 5 * 16 }, { 16, 32 } },
        { { 14 * 16, 5 * 16 }, { 16, 32 } },
        { { 15 * 16, 5 * 16 }, { 16, 32 } },
    });

    AnimationController animationController({
        { "default", animation }
    }, "default");

    auto& anim = mainScene->Create();
    anim.AddComponent<Transform>(glm::vec2{ -1, -1 }, 0.0f, glm::vec2{ 1, 2 });
    anim.AddComponent<SpriteComponent>();
    anim.AddComponent<AnimatorComponent>(animationController);

    auto& ui = mainScene->Create();
    ui.AddComponent<UiComponent>();
    auto& c = ui.GetComponent<UiComponent>().Container;
    auto bar = MakeRef<ProgressBar>(MakeRef<Font>("assets/fonts/arial.ttf", 25));
    bar->Width(50, true).Height(30).CenterX().MarginBottom(5, true);
    c.Add(std::dynamic_pointer_cast<UiBlock, ProgressBar>(bar));

    auto b1 = MakeRef<UiBlock>();
    b1->MarginLeft(20).MarginTop(20).MarginBottom(20).Width(25, true);

    auto l1 = MakeRef<Label>("The quick brown fox jumps over the lazy dog", MakeRef<Font>("assets/fonts/comic.ttf", 50), glm::vec4{ 1, 0, 1, 0.5f });
    l1->MarginTop(0).MarginLeft(0);

    auto b2 = MakeRef<UiBlock>();
    b2->MarginTop(10, true).MarginRight(20).Width(300).Height(200);

    auto b3 = MakeRef<UiBlock>();
    b3->MarginBottom(0).Width(50, true).Height(30).CenterX();

    auto b4 = MakeRef<UiBlock>();
    b4->MarginLeft(100).MarginBottom(50, true).Width(50).Height(50).CenterBoth();
    c.Add(b1);
    c.Add(b2);
    c.Add(b3);
    c.Add(b4);
    c.Add(l1);

    Application::GetSceneManager().Add("main", mainScene);
    Application::GetSceneManager().Show("main");

    Application::Run();

    Application::Quit();
}
