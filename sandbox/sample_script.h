#pragma once

#include "shadow/shadow.h"
using namespace Shadow;

class SampleScript : public Script {
    void OnLoad() override {
        SH_WARN("Script on load");
    }

    void VariableUpdate(float delta) override {
        auto& transform = GetComponent<Transform>();

        float speed = 5.0f;

        if (Input::IsKeyPressed(Key::W))
            transform.Position.y += speed * delta;
        if (Input::IsKeyPressed(Key::A))
            transform.Position.x -= speed * delta;
        if (Input::IsKeyPressed(Key::S))
            transform.Position.y -= speed * delta;
        if (Input::IsKeyPressed(Key::D))
            transform.Position.x += speed * delta;

    }
};
