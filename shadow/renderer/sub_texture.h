#pragma once

#include "shadow/renderer/texture.h"

namespace Shadow {
class SubTexture {
public:
    SubTexture() = default;
    explicit SubTexture(Ref<Texture> texture);
    SubTexture(Ref<Texture> texture, const glm::vec4& texCoords);
    SubTexture(Ref<Texture> texture, const glm::vec2& offset, const glm::vec2& size);

    Ref<Texture> GetTexture() const { return mTexture; }
    glm::vec4 const& GetTexCoords() const { return mTexCoords; }

private:
    Ref<Texture> mTexture;
    glm::vec4 mTexCoords { 0.0f, 0.0f, 1.0f, 1.0f };
};
}