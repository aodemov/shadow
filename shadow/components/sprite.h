#pragma once

#include "shadow/renderer/texture.h"
#include "shadow/renderer/sub_texture.h"

namespace Shadow {

class Sprite {
public:
    Sprite() = default;
    explicit Sprite(Ref<Texture> texture, float rotation = 0)
        : mTexture(std::move(texture)),
          mRotation(rotation) {}

    explicit Sprite(SubTexture const& texture, float rotation = 0)
        : mTexture(texture),
          mRotation(rotation) {}

    SubTexture mTexture;

    float mRotation = 0.0f;
    float mZ = 0.0f;
    bool mFlipX = false, mFlipY = false;
    glm::vec4 mTint = { 1.0f, 1.0f, 1.0f, 1.0f };
};

}
