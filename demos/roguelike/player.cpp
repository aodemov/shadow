#include "player.h"

void Player::Load() {
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

    mSprite = MakeScope<AnimatedSprite>(animationController, glm::vec3{ 10, 17, 0.0f }, glm::vec2{ 1, 2 });
}

void Player::Update(float delta) {
    mSprite->Update(delta);

    glm::vec2 velocity(0.0f);

    if (Input::IsKeyPressed(Key::W))
        velocity.y += mSpeed;
    if (Input::IsKeyPressed(Key::A))
        velocity.x -= mSpeed;
    if (Input::IsKeyPressed(Key::S))
        velocity.y -= mSpeed;
    if (Input::IsKeyPressed(Key::D))
        velocity.x += mSpeed;

    mSprite->Position() += glm::vec3{ velocity, 0.0f } * delta;

    if (fabs(velocity.x) + fabs(velocity.y) > 0.01)
        mSprite->GetAnimationController().SetState("run");
    else
        mSprite->GetAnimationController().SetState("idle");

    mSprite->FlipX() = velocity.x < 0;

}

void Player::Draw() {
    mSprite->Draw();
}
