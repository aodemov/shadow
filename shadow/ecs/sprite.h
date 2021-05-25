#pragma once

#include <shadow/shadow.h>

#include <utility>

namespace Shadow {

class Sprite {
public:
    explicit Sprite(Ref<Texture> texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : mTexture(MakeRef<SubTexture>(std::move(texture))),
          mPosition(position),
          mSize(size),
          mRotation(rotation) {}

    explicit Sprite(Ref<SubTexture> texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : mTexture(std::move(texture)),
          mPosition(position),
          mSize(size),
          mRotation(rotation) {}

    void Draw();

    glm::vec3 GetPosition() const { return mPosition; }
    void SetPosition(glm::vec3 position) { mPosition = position; }

    glm::vec2 GetSize() const { return mSize; }
    void SetSize(glm::vec2 size) { mSize = size; }

    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

private:
    glm::vec3 mPosition;
    glm::vec2 mSize;
    float mRotation;
    Ref<SubTexture> mTexture;
};

}
