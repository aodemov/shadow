#include "player.h"

void Player::Load() {
    auto tilemap = MakeRef<Texture>("assets/textures/tilemap2.png");
    Animation animation(tilemap, 0.33f, {
            {{ 8 * 16, 30 * 16 }, { 16, 32 }},
            {{ 9 * 16, 30 * 16 }, { 16, 32 }},
            {{ 10 * 16, 30 * 16 }, { 16, 32 }},
            {{ 11 * 16, 30 * 16 }, { 16, 32 }},
    });


    mSprite = MakeScope<AnimatedSprite>(animation, glm::vec3{ 10, 17, 0.0f }, glm::vec2{ 1, 2 });
}

void Player::Update(float delta) {
    mSprite->Update(delta);

    if (Input::IsKeyPressed(Key::W))
        mSprite->Position().y += mSpeed * delta;
    if (Input::IsKeyPressed(Key::A))
        mSprite->Position().x -= mSpeed * delta;
    if (Input::IsKeyPressed(Key::S))
        mSprite->Position().y -= mSpeed * delta;
    if (Input::IsKeyPressed(Key::D))
        mSprite->Position().x += mSpeed * delta;
}

void Player::Draw() {
    mSprite->Draw();
}
