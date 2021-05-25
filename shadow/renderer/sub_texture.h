#pragma once

#include "shadow/renderer/texture.h"

namespace Shadow {
class SubTexture {
public:
    SubTexture(const Ref<Texture>& texture);
    SubTexture(const Ref<Texture>& texture, const glm::vec4& texCoords);
    SubTexture(const Ref<Texture>& texture, const glm::vec2& size, const glm::vec2& offset);

    const Ref<Texture> GetTexture() const { return _texture; }
    const glm::vec2* GetTexCoords() const { return _texCoords; }

private:
    Ref<Texture> _texture;
    glm::vec2 _texCoords[4];
};
}