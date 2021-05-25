#include "texture.h"

#include <glad/gl.h>
#include "lib/stb_image/stb_image.h"

namespace Shadow {

Texture::Texture(uint32_t width, uint32_t height, uint32_t rendererId)
    : mWidth(width),
      mHeight(height),
      mRendererId(rendererId) {}

Texture::Texture(const std::string &path)
    : mPath(path),
      mRendererId(0)
{
    int w, h, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(mPath.c_str(), &w, &h, &channels, 0);

    if (!data) {
        SH_CORE_ERROR("Cannot load image from: {0}", mPath);
    }

    mWidth = w;
    mHeight = h;

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

    glCreateTextures(GL_TEXTURE_2D, 1, &mRendererId);
    glTextureStorage2D(mRendererId, 1, internalFormat, (int)mWidth, (int)mHeight);

    glTextureParameteri(mRendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(mRendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(mRendererId, 0, 0, 0, (int)mWidth, (int)mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Ref<Texture> Texture::CreateWhiteTexture() {
    uint32_t id;
    glGenTextures(1, &id);

    GLubyte data[] = { 255, 255, 255, 255 };

    glBindTexture(GL_TEXTURE_2D, id);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    return Ref<Texture>(new Texture(1, 1, id));
}

bool Texture::operator==(const Texture &other) const {
    return mRendererId == other.mRendererId;
}

Texture::~Texture() {
    glDeleteTextures(1, &mRendererId);
}

void Texture::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, mRendererId);
}
}