#pragma once

#include <shadow/shadow.h>
#include "health_bar.h"

using namespace Shadow;

class Player : public Script {
public:
    void OnLoad() override {
        AddComponent<TagComponent>("Player");

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

        AddComponent<Transform>(glm::vec2{ 15, 20 }, 0.0f, glm::vec2{ 1, 2 });
        AddComponent<SpriteComponent>().sprite.mZ = 1.0f;
        AddComponent<AnimatorComponent>(animationController);

        AddComponent<ColliderComponent>(glm::vec4{ 0.1, 0, 0.9, 0.9 });
        AddComponent<TriggerComponent>(glm::vec4{ 0.1, 0, 0.9, 0.9 });
        AddComponent<RigidbodyComponent>();

        auto camera = CreateObject();
        camera.AddComponent<Transform>();
        auto& c = camera.AddComponent<CameraComponent>();
        c.cameraController.SetPosition({ 0, 0, 0 });
        c.cameraController.SetRotation(0);
        c.cameraController.SetZoom(6);
        GetScene().SetCamera(&c.cameraController.GetCamera());
        mCamera = &c.cameraController;

        // Ui
        auto ui = CreateObject();
        auto& container = ui.AddComponent<UiComponent>().Container;
        healthBar = MakeRef<HealthBar>(MakeRef<Font>("assets/fonts/nintendo.ttf", 22));
        healthBar->Width(300).Height(30).MarginLeft(50).MarginBottom(35);
        container.Add(healthBar);
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

        healthBar->SetValue(100.0f * health / maxHealth);

        mCamera->SetPosition({transform.Position.x, transform.Position.y, 0.0f});
    }

    void Damage(float damage) {
        health -= damage;
    }

private:
    float mSpeed = 5;
    CameraController* mCamera;
    glm::vec2 mVelocity;
    float maxHealth = 100;
    float health = maxHealth;
    Ref<HealthBar> healthBar;
};

