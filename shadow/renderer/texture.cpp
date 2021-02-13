#include "texture.h"

#include <glad/gl.h>
#include "stb_image.h"

namespace Shadow {

Texture::Texture(const std::string &path_)
    : path(path_),
      rendererId(0)
{
    int width_, height_, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width_, &height_, &channels, 0);

    if (!data) {
        SH_CORE_ERROR("Cannot load image from: {0}", path);
    }

    width = width_;
    height = height_;

    glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
    glTextureStorage2D(rendererId, 1, GL_RGB8, width, height);

    glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(rendererId, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &rendererId);
}

void Texture::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, rendererId);
}
}