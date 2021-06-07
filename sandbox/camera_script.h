#pragma once

#include "shadow/shadow.h"
using namespace Shadow;

class CameraScript : public Script {
public:
    void OnLoad() override {
    }

    void VariableUpdate(float delta) override {
        auto& cam = GetComponent<CameraComponent>().cameraController;

        if (Input::IsKeyPressed(Key::W))
            cameraPosition.y += cameraSpeed * delta;
        if (Input::IsKeyPressed(Key::A))
            cameraPosition.x -= cameraSpeed * delta;
        if (Input::IsKeyPressed(Key::S))
            cameraPosition.y -= cameraSpeed * delta;
        if (Input::IsKeyPressed(Key::D))
            cameraPosition.x += cameraSpeed * delta;
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
        if (Input::IsKeyPressed(Key::R)) {
            cameraSpeed += 0.4f;
        }
        if (Input::IsKeyPressed(Key::F)) {
            cameraSpeed -= 0.4f;
        }

        cam.SetPosition(cameraPosition);
        cam.SetZoom(cameraZoom);
        cam.SetRotation(cameraRotation);
    }

private:
    glm::vec3 cameraPosition{0.0f};
    float cameraSpeed{8.0f};
    float cameraZoom{10.0f};
    float cameraRotation{0.0f};
};
