#pragma once

#include "shadow/renderer/texture.h"

namespace Shadow {
class SubTexture {
public:
    SubTexture(const std::shared_ptr<Texture>& texture);
    SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec4& texCoords);
    SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& size, const glm::vec2& offset);

    const std::shared_ptr<Texture> GetTexture() const { return _texture; }
    const glm::vec2* GetTexCoords() const { return _texCoords; }

private:
    std::shared_ptr<Texture> _texture;
    glm::vec2 _texCoords[4];
};
}