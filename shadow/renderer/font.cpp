#include "font.h"

#include <glad/gl.h>

#include "shadow/core/utils/file.h"


namespace Shadow {

Font::Font(const std::string &path, int fontSize)
    : mSize(fontSize) {
    auto fontData = File::Read(path);

    // Font info
    stbtt_InitFont(&mFontInfo, reinterpret_cast<const unsigned char *>(fontData.c_str()), 0);
    mScale = stbtt_ScaleForPixelHeight(&mFontInfo, mSize);
    int StbAscent;
    int StbDescent;
    int StbLineGap;
    stbtt_GetFontVMetrics(&mFontInfo, &StbAscent, &StbDescent, &StbLineGap);
    mAscent = StbAscent * mScale;
    mDescent = StbDescent * mScale;
    mLineGap = StbLineGap * mScale;
    mLineAdvance = mAscent - mDescent + mLineGap;

    // Packing atlas
    auto atlasData = std::make_unique<uint8_t[]>(cAtlasWidth * cAtlasHeight);

    mCharInfo = std::make_unique<stbtt_packedchar[]>(cCharCount);

    stbtt_pack_context context;
    if (!stbtt_PackBegin(&context, atlasData.get(), cAtlasWidth, cAtlasHeight, 0, 1, nullptr))
        SH_CORE_ERROR("Failed to initialize font");

    stbtt_PackSetOversampling(&context, cOversampleX, cOversampleY);
    if (!stbtt_PackFontRange(&context, reinterpret_cast<const unsigned char *>(fontData.c_str()), 0,
                             mSize, cFirstChar, cCharCount, mCharInfo.get()))
        SH_CORE_ERROR("Failed to pack font");
    stbtt_PackEnd(&context);

    // Creating texture
    uint32_t tid;
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cAtlasWidth, cAtlasHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, atlasData.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    mTexture = MakeRef<Texture>(cAtlasWidth, cAtlasHeight, tid);
}

Font::Glyph Font::GetTexCoords(uint32_t codepoint, glm::vec2* offset) {
    stbtt_aligned_quad q;

    stbtt_GetPackedQuad(mCharInfo.get(), cAtlasWidth, cAtlasHeight,
                        codepoint - cFirstChar, &offset->x, &offset->y, &q, 1);

    Glyph g{};
    g.x0 = q.x0;
    g.x1 = q.x1;
    g.y0 = -q.y0;
    g.y1 = -q.y1;
    g.s0 = q.s0;
    g.s1 = q.s1;
    g.t0 = q.t0;
    g.t1 = q.t1;

    return g;
}

float Font::GetStringWidth(std::string const& str) {
    float width = 0;

    for (auto c : str) {
        width += mCharInfo[c - cFirstChar].xadvance;
    }

    return width;
}

}