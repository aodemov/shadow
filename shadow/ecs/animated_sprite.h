#pragma once

#include "shadow/ecs/animation_controller.h"

namespace Shadow {
class AnimatedSprite {
public:
    explicit AnimatedSprite(AnimationController animationSM, glm::vec3 position = {0, 0, 0}, glm::vec2 size = {1, 1}, float rotation = 0)
    : mAnimationController(std::move(animationSM)),
      mPosition(position),
      mSize(size),
      mRotation(rotation) {}

    void Update(float delta);
    void Draw();

    glm::vec3& Position() { return mPosition; }
    glm::vec2& Size() { return mSize; }
    float& Rotation() { return mRotation; }
    bool& FlipX() { return mFlipX; }
    bool& FlipY() { return mFlipY; }

    AnimationController& GetAnimationController() { return mAnimationController; }

private:
    glm::vec3 mPosition;
    glm::vec2 mSize;
    AnimationController mAnimationController;

    float mRotation = 0.0f;
    bool mFlipX = false, mFlipY = false;

    glm::vec4 mTint = { 1.0f, 1.0f, 1.0f, 1.0f };
};
}
