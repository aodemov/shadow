#pragma once

#include "shadow/renderer/texture.h"

namespace Shadow {
class SubTexture {
public:
    explicit SubTexture(Ref<Texture> texture);
    SubTexture(Ref<Texture> texture, const glm::vec4& texCoords);
    SubTexture(Ref<Texture> texture, const glm::vec2& offset, const glm::vec2& size, float rotation = 0.0f);

    Ref<Texture> GetTexture() const { return mTexture; }
    glm::vec4 const& GetTexCoords() const { return mTexCoords; }
    float GetRotation() const { return mRotation; }

private:
    Ref<Texture> mTexture;
    glm::vec4 mTexCoords;
    float mRotation = 0.0f;
};
}