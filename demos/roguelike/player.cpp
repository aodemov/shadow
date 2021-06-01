#include "player.h"

void Player::Load() {
    auto tex = MakeRef<SubTexture>(MakeRef<Texture>("assets/textures/tilemap2.png"),
            glm::vec2{ 8 * 16, 30 * 16 }, glm::vec2{ 16, 2 * 16 });
    mSprite = MakeRef<Sprite>(tex, glm::vec3{ 10, 17, 0.0f }, glm::vec2{ 1, 2 });
}

void Player::Update(float delta) {
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
