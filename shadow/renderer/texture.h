#pragma once

namespace Shadow {

class Texture {
public:
    explicit Texture(std::string const& path);
    Texture(uint32_t width, uint32_t height, uint32_t rendererId);

    ~Texture();

    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }

    void Bind(uint32_t slot = 0) const;

    bool operator==(const Texture& other) const;

    static Ref<Texture> CreateWhiteTexture();

private:
    std::string mPath;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mRendererId;
};

}
