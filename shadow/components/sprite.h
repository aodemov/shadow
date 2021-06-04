#pragma once

#include <shadow/shadow.h>

#include <utility>

namespace Shadow {

class Sprite {
public:
    explicit Sprite(Ref<Texture> texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : mTexture((std::move(texture))),
          mPosition(position),
          mSize(size),
          mRotation(rotation) {}

    explicit Sprite(SubTexture const& texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : mTexture(texture),
          mPosition(position),
          mSize(size),
          mRotation(rotation) {}

    void Draw();

    glm::vec3& Position() { return mPosition; }
    glm::vec2& Size() { return mSize; }
    float& Rotation() { return mRotation; }

private:
    glm::vec3 mPosition;
    glm::vec2 mSize;
    SubTexture mTexture;

    float mRotation = 0.0f;
    bool mFlipX = false, mFlipY = false;

    glm::vec4 mTint = { 1.0f, 1.0f, 1.0f, 1.0f };
};

}
