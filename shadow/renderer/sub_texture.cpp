#include "sub_texture.h"

#include <utility>

namespace Shadow {
SubTexture::SubTexture(Ref<Texture> texture)
    : mTexture(std::move(texture)) {
    mTexCoords[0] = {0.0f, 0.0f };
    mTexCoords[1] = {1.0f, 0.0f };
    mTexCoords[2] = {1.0f, 1.0f };
    mTexCoords[3] = {0.0f, 1.0f };
}

SubTexture::SubTexture(Ref<Texture> texture, const glm::vec4& texCoords)
    : mTexture(std::move(texture)) {
    mTexCoords[0] = {texCoords.x, texCoords.y };
    mTexCoords[1] = {texCoords.z, texCoords.y };
    mTexCoords[2] = {texCoords.z, texCoords.w };
    mTexCoords[3] = {texCoords.x, texCoords.w };
}

SubTexture::SubTexture(Ref<Texture> texture, const glm::vec2 &size, const glm::vec2 &offset)
    : mTexture(std::move(texture)) {
    glm::vec4 texCoords = {offset.x / mTexture->GetWidth(),
                           offset.y / mTexture->GetHeight(),
                           (offset.x + size.x) / mTexture->GetWidth(),
                           (offset.y + size.y) / mTexture->GetHeight() };

    mTexCoords[0] = {texCoords.x, texCoords.y };
    mTexCoords[1] = {texCoords.z, texCoords.y };
    mTexCoords[2] = {texCoords.z, texCoords.w };
    mTexCoords[3] = {texCoords.x, texCoords.w };
}
}