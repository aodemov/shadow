#include "texture.h"

#include <glad/gl.h>
#include "lib/stb_image/stb_image.h"

namespace Shadow {

Texture::Texture(uint32_t width, uint32_t height, uint32_t rendererId)
    : width(width),
      height(height),
      rendererId(rendererId) {}

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

std::shared_ptr<Texture> Texture::CreateWhiteTexture() {
    uint32_t id;
    glGenTextures(1, &id);

    GLubyte data[] = { 255, 255, 255, 255 };

    glBindTexture(GL_TEXTURE_2D, id);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    return std::shared_ptr<Texture>(new Texture(1, 1, id));
}

bool Texture::operator==(const Texture &other) {
    return rendererId == other.rendererId;
}

Texture::~Texture() {
    glDeleteTextures(1, &rendererId);
}

void Texture::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, rendererId);
}
}