#include "texture.h"

#include <glad/gl.h>
#include "lib/stb_image/stb_image.h"

namespace Shadow {

Texture::Texture(const std::string &path_)
    : path(path_),
      rendererId(0)
{
    int width_, height_, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.c_str(), &width_, &height_, &channels, 0);

    if (!data) {
        SH_CORE_ERROR("Cannot load image from: {0}", path);
    }

    width = width_;
    height = height_;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    } else if (channels == 3) {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    if ((internalFormat & dataFormat) == 0) {
        SH_CORE_ERROR("Image format not supported ({0})", path);
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
    glTextureStorage2D(rendererId, 1, internalFormat, width, height);

    glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(rendererId, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &rendererId);
}

void Texture::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, rendererId);
}
}