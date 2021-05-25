#include <iostream>
#include <string>
#include <cmath>
#include "shadow/shadow.h"
#include <glm/gtx/closest_point.hpp>

#include "snake.h"
#include "borders.h"
#include "food.h"


using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
        : borders(10, 10),
          food(9, 9)
    {
        food.Generate(5);
    }

    void Load() override {
        Render::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

        cameraController.SetPosition({ 0, 0, 0 });
        cameraController.SetRotation(0);
        cameraController.SetZoom(10);
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
        if (gameOver)
            return;

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
                break;
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


        Render::Clear();

        Render::BeginScene(cameraController.GetCamera());

        // Draw borders
        const float borderWidth = 0.3f;
        const glm::vec4 borderColor = { 0, 0, 0, 0.8f };
        auto& bc = borders.GetCorners();
        Render::DrawLine(bc[0], bc[1], borderWidth, borderColor);
        Render::DrawLine(bc[1], bc[2], borderWidth, borderColor);
        Render::DrawLine(bc[2], bc[3], borderWidth, borderColor);
        Render::DrawLine(bc[3], bc[0], borderWidth, borderColor);

        // Draw snake
        float snakeWidth = 0.2f;
        for (int i = 0; i < b.size() - 1; i++) {
            glm::vec4 color = { 52.0f / 256, 235.0f / 256, 161.0f / 256, 0.8f };
            Render::DrawLine(b[i], b[i+1], snakeWidth, color);
        }

        // Draw food
        const float foodSize = 0.3f;
        for (auto& p : food.GetPieces()) {
            glm::vec4 color = { 1.0f, 0, 0, 0.8f};
            Render::DrawRect({p.position, 0.0f}, (float)sqrt(p.value) * glm::vec2(foodSize, foodSize), color, 45.0f);
        }


        Render::EndScene();
    }

private:
    CameraController cameraController;

    Snake snake;
    Borders borders;
    Food food;

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
