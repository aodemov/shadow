#include "sub_texture.h"

namespace Shadow {
SubTexture::SubTexture(const std::shared_ptr<Texture> &texture)
    : _texture(texture) {
    _texCoords[0] = { 0.0f, 0.0f };
    _texCoords[1] = { 1.0f, 0.0f };
    _texCoords[2] = { 1.0f, 1.0f };
    _texCoords[3] = { 0.0f, 1.0f };
}

SubTexture::SubTexture(const std::shared_ptr<Texture> &texture, const glm::vec4& texCoords)
    : _texture(texture) {
    _texCoords[0] = { texCoords.x, texCoords.y };
    _texCoords[1] = { texCoords.z, texCoords.y };
    _texCoords[2] = { texCoords.z, texCoords.w };
    _texCoords[3] = { texCoords.x, texCoords.w };
}

SubTexture::SubTexture(const std::shared_ptr<Texture> &texture, const glm::vec2 &size, const glm::vec2 &offset)
    : _texture(texture) {
    glm::vec4 texCoords = { offset.x / _texture->GetWidth(),
                            offset.y / _texture->GetHeight(),
                            (offset.x + size.x)  / _texture->GetWidth(),
                            (offset.y + size.y) / _texture->GetHeight() };

    _texCoords[0] = { texCoords.x, texCoords.y };
    _texCoords[1] = { texCoords.z, texCoords.y };
    _texCoords[2] = { texCoords.z, texCoords.w };
    _texCoords[3] = { texCoords.x, texCoords.w };
}
}