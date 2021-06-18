#pragma once

#include <shadow/shadow.h>

using namespace Shadow;

class Player : public Script {
public:
    void OnLoad() override {
        auto tilemap = MakeRef<Texture>("assets/textures/tilemap2.png");

        const int P = 28;
        Animation idleAnimation(tilemap, 0.33f, {
                {{ 8  * 16, P * 16 }, { 16, 32 }},
                {{ 9  * 16, P * 16 }, { 16, 32 }},
                {{ 10 * 16, P * 16 }, { 16, 32 }},
                {{ 11 * 16, P * 16 }, { 16, 32 }},
        });

        Animation runAnimation(tilemap, 0.33f, {
                {{ 12 * 16, P * 16 }, { 16, 32 }},
                {{ 13 * 16, P * 16 }, { 16, 32 }},
                {{ 14 * 16, P * 16 }, { 16, 32 }},
                {{ 15 * 16, P * 16 }, { 16, 32 }},
        });

        AnimationController animationController({
            { "run", runAnimation },
            { "idle", idleAnimation },
        }, "idle");

        AddComponent<Transform>(glm::vec2{ 10, 17 }, 0.0f, glm::vec2{ 1, 2 });
        AddComponent<SpriteComponent>().sprite.mZ = 1.0f;
        AddComponent<AnimatorComponent>(animationController);

        AddComponent<ColliderComponent>(glm::vec4{ 0, 0, 1, 1.2 });
        AddComponent<RigidbodyComponent>();

        auto camera = CreateObject();
        camera.AddComponent<Transform>();
        auto& c = camera.AddComponent<CameraComponent>();
        c.cameraController.SetPosition({ 0, 0, 0 });
        c.cameraController.SetRotation(0);
        c.cameraController.SetZoom(6);
        GetScene().SetCamera(&c.cameraController.GetCamera());
        mCamera = &c.cameraController;
    }
    void VariableUpdate(float delta) override {
        auto& transform = GetComponent<Transform>();
        auto& animationController = GetComponent<AnimatorComponent>().animationController;
        auto& sprite = GetComponent<SpriteComponent>().sprite;
        auto& collider = GetComponent<ColliderComponent>();
        auto& rb = GetComponent<RigidbodyComponent>();


        mVelocity = glm::vec2{0.0f};
        if (Input::IsKeyPressed(Key::W))
            mVelocity.y += mSpeed;
        if (Input::IsKeyPressed(Key::A))
            mVelocity.x -= mSpeed;
        if (Input::IsKeyPressed(Key::S))
            mVelocity.y -= mSpeed;
        if (Input::IsKeyPressed(Key::D))
            mVelocity.x += mSpeed;

        if (fabs(mVelocity.x) + fabs(mVelocity.y) > 0.01)
            animationController.SetState("run");
        else
            animationController.SetState("idle");

        sprite.mFlipX = mVelocity.x < 0;

        rb.Velocity = mVelocity;

        mCamera->SetPosition({transform.Position.x, transform.Position.y, 0.0f});
    }

    void FixedUpdate(float delta) override {

    }

private:
    float mSpeed = 5;
    CameraController* mCamera;
    glm::vec2 mVelocity;
};

