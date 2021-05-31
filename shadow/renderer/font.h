#pragma once

#include "shadow/renderer/texture.h"
#include "shadow/renderer/sub_texture.h"
#include "lib/stb_truetype/stb_truetype.h"


namespace Shadow {
class Font {
public:
    struct Glyph {
        float x0,y0,s0,t0;
        float x1,y1,s1,t1;
    };

    explicit Font(std::string const& path, int fontSize);

    Ref<Texture> GetTexture() const { return mTexture; }

    Glyph GetTexCoords(uint32_t c, glm::vec2* offset);
    float GetStringWidth(std::string const& str);
private:
    Ref<Texture> mTexture;
    std::unique_ptr<stbtt_packedchar[]> mCharInfo;
    uint32_t mSize;
//    stbtt_fontinfo mFontInfo;
//    float scale;
//    float ascent;
//    float descent;
//    float lineGap;
//    float lineAdvance;

    const uint32_t cAtlasWidth = 1024;
    const uint32_t cAtlasHeight = 1024;
    const uint32_t cOversampleX = 2;
    const uint32_t cOversampleY = 2;
    const uint32_t cFirstChar = ' ';
    const uint32_t cCharCount = '~' - ' ';
};
}
