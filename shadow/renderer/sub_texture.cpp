#include "sub_texture.h"

#include <utility>

namespace Shadow {
SubTexture::SubTexture(Ref<Texture> texture)
    : mTexture(std::move(texture)) {
    mTexCoords = { 0.0f, 0.0f, 1.0f, 1.0f };
}

SubTexture::SubTexture(Ref<Texture> texture, const glm::vec4& texCoords)
    : mTexture(std::move(texture)),
      mTexCoords(texCoords) {}

SubTexture::SubTexture(Ref<Texture> texture, const glm::vec2 &offset, const glm::vec2 &size, float rotation)
    : mTexture(std::move(texture)),
      mRotation(rotation) {
    mTexCoords = {offset.x / (float)mTexture->GetWidth(),
                           offset.y / (float)mTexture->GetHeight(),
                           (offset.x + size.x) / (float)mTexture->GetWidth(),
                           (offset.y + size.y) / (float)mTexture->GetHeight() };
}
}