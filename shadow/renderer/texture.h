#pragma once

namespace Shadow {

class Texture {
public:
    Texture(std::string const& path_);

    ~Texture();

    uint32_t GetWidth() const { return width; }
    uint32_t GetHeight() const { return height; }

    void Bind(uint32_t slot = 0) const;

private:
    std::string path;
    uint32_t width;
    uint32_t height;
    uint32_t rendererId;
};

}