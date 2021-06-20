#pragma once

#include <shadow/shadow.h>

#include "player.h"

using namespace Shadow;

class Enemy : public Script {
public:
    void OnLoad() override {
        auto tilemap = MakeRef<Texture>("assets/textures/tilemap2.png");

        const int P = 13;
        Animation idleAnimation(tilemap, 0.66f, {
                {{ 1  * 16, P * 16 }, { 32, 32 }},
                {{ 3  * 16, P * 16 }, { 32, 32 }},
                {{ 5  * 16, P * 16 }, { 32, 32 }},
                {{ 7  * 16, P * 16 }, { 32, 32 }},
        });

        Animation runAnimation(tilemap, 0.5f, {
                {{ 9  * 16, P * 16 }, { 32, 32 }},
                {{ 11 * 16, P * 16 }, { 32, 32 }},
                {{ 13 * 16, P * 16 }, { 32, 32 }},
                {{ 15 * 16, P * 16 }, { 32, 32 }},
        });

        AnimationController animationController({
                        { "run", runAnimation },
                        { "idle", idleAnimation },
                }, "idle");

        AddComponent<Transform>(glm::vec2{ 20, 24 }, 0.0f, glm::vec2{ 2, 2 });
        AddComponent<SpriteComponent>().sprite.mZ = 1.0f;
        AddComponent<AnimatorComponent>(animationController);
        AddComponent<ColliderComponent>(glm::vec4{ 0.3, 0., 1.7, 0.9 });
        AddComponent<RigidbodyComponent>();

        AddComponent<TriggerComponent>(glm::vec4{ -0.2, -0.2, 2.2, 2.2 });

        playerTransform = &GetEntityWithTag("Player").GetComponent<Transform>();
    }
    void VariableUpdate(float delta) override {
        auto& transform = GetComponent<Transform>();
        auto& animationController = GetComponent<AnimatorComponent>().animationController;
        auto& sprite = GetComponent<SpriteComponent>().sprite;
        auto& trigger = GetComponent<TriggerComponent>();
        auto& rb = GetComponent<RigidbodyComponent>();

        // Movement
        glm::vec2 direction = glm::normalize(playerTransform->Position - transform.Position);
        glm::vec2 velocity = direction * mSpeed;

        if (fabs(velocity.x) + fabs(velocity.y) > 0.01)
            animationController.SetState("run");
        else
            animationController.SetState("idle");

        sprite.mFlipX = velocity.x < 0;

        rb.Velocity = velocity;

        // Player attack
        if (attackTime > 0)
            attackTime = std::max(attackTime - delta, 0.0f);

        if (!trigger.Hits.empty()) {
            for (auto& entity : trigger.Hits) {
                if (entity.HasComponent<TagComponent>() && entity.GetComponent<TagComponent>().Tag == "Player") {
                    auto player = static_cast<Player*>(entity.GetComponent<ScriptComponent>().script);
                    if (attackTime == 0.0f) {
                        player->Damage(attack);
                        attackTime = attackCooldown;
                    }
                }
            }
        }
    }

    void FixedUpdate(float delta) override {

    }

private:
    float mSpeed = 3;
    float attack = 5;
    float attackCooldown = 0.5f;
    float attackTime = 0;
    Transform* playerTransform = nullptr;
};

