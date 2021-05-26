#pragma once

#include "shadow/renderer/texture.h"
#include "shadow/renderer/sub_texture.h"
#include "lib/stb_truetype/stb_truetype.h"


namespace Shadow {
class Font {
public:
    struct GlyphInfo {
        float x0, y0, x1, y1;
        float s0, t0, s1, t1;
    };

    explicit Font(std::string const& path);

    Ref<SubTexture> GetTexture() const { return mTexture; }

    stbtt_aligned_quad GetTexCoords(uint32_t c, glm::vec2* offset);
    float scale;
private:
    Ref<SubTexture> mTexture;
    const uint32_t size = 20;
    const uint32_t atlasWidth = 1024;
    const uint32_t atlasHeight = 1024;
    const uint32_t oversampleX = 2;
    const uint32_t oversampleY = 2;
    const uint32_t firstChar = ' ';
    const uint32_t charCount = '~' - ' ';
    stbtt_fontinfo info;
    std::unique_ptr<stbtt_packedchar[]> charInfo;
};
}
