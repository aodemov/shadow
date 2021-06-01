#include <iostream>
#include <string>
#include <cmath>
#include "shadow/shadow.h"
#include <glm/gtx/closest_point.hpp>

#include "snake.h"
#include "borders.h"
#include "food.h"

#include "scoreboard.h"


using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
        : borders(10, 10),
          food(9, 9)
    {
        NewGame();
    }

    void Load() override {
        Render::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

        cameraController.SetPosition({ 0, 0, 0 });
        cameraController.SetRotation(0);
        cameraController.SetZoom(6);

        Application::GetEventBus().AddListener<KeyPressedEvent>([&](auto e) {
           if (gameOver && e.GetKeyCode() == Key::Space) {
               NewGame();
           }
        });

        font = MakeRef<Font>("assets/segoeui.ttf", 32 * 2);

        mScoreboard = MakeRef<Scoreboard>();
        mScoreboard->MarginRight(20).MarginTop(20).Width(300).Height(120);
        UI::Add(mScoreboard);
    }

    void Show() override {
    }

    void Hide() override {
    }
    void Destroy() override {
    }

    void FixedUpdate(float delta) override {
        
    }

    void NewGame() {
        snake = Snake();
        food = Food(9, 9);
        food.Generate(3);

        gameOver = false;
    }

    void VariableUpdate(float delta) override {
        Render::Clear();

        if (gameOver) {
            UI::Begin();

            Render::DrawText("Lol, u died",{ Application::GetWindow().GetWidth() / 2 - 50, Application::GetWindow().GetHeight() / 2 - 20, 0 }, font, {0,0,0,1});
            Render::DrawText("Press space to continue",{ Application::GetWindow().GetWidth() / 2 - 200, Application::GetWindow().GetHeight() / 2 + 20, 0 }, font, {0,0,0,1});

            UI::End();

            return;
        }

        // Snake input
        if (Input::IsKeyPressed(Key::Up)) {
            snake.SetDirection(Snake::Direction::Up);
        } else if (Input::IsKeyPressed(Key::Down)) {
            snake.SetDirection(Snake::Direction::Down);
        } else if (Input::IsKeyPressed(Key::Left)) {
            snake.SetDirection(Snake::Direction::Left);
        } else if (Input::IsKeyPressed(Key::Right)) {
            snake.SetDirection(Snake::Direction::Right);
        }
        snake.Update(delta);


        // Food collision
        for (auto it = food.GetPieces().begin(); it < food.GetPieces().end(); ++it) {
            if (glm::distance(it->position, snake.GetBody()[0]) < 0.2f) {
                snake.Feed(it->value);

                food.GetPieces().erase(it);
                food.Generate(1);
//                break;
            }
        }

        // Snake border collision
        auto& h = snake.GetBody()[0];
        float wi = borders.GetDimensions().x;
        float he = borders.GetDimensions().y;
        if (h.x >= wi / 2 || h.x <= -wi / 2 || h.y > he / 2 || h.y < -he / 2) {
            gameOver = true;
            SH_INFO("Border collision");
            return;
        }

        // Snake itself collision
        auto& b = snake.GetBody();
        for (int i = 2; i < b.size() - 1; i++) {
            if (glm::distance(b[0], glm::closestPointOnLine(b[0], b[i], b[i+1])) < 0.2f) {
                gameOver = true;
                SH_INFO("Itself collision");
                return;
            }
        }

        Render::BeginScene(cameraController.GetCamera());

        borders.Draw();
        snake.Draw();
        food.Draw();

        Render::EndScene();

        mScoreboard->SetScore((int)round(snake.GetLength() * 10));

        UI::Begin();

//        Render::DrawText("Score: " + std::to_string((int)round(snake.GetLength() * 10)), { Application::GetWindow().GetWidth() - 300, 100, 0 }, font, {0,0,0,1});

        UI::End();
    }

private:
    CameraController cameraController;

    Snake snake;
    Borders borders;
    Food food;

    Ref<Scoreboard> mScoreboard;
    Ref<Font> font;
    bool gameOver = false;
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
