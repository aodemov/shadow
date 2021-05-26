#include "font.h"

#include <glad/gl.h>


namespace Shadow {

std::string readFile(std::string const& path) {
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    std::string contents;

    if(fs) {
        fs.seekg(0, std::ios::end);
        size_t size = fs.tellg();
        if (size == -1) {
            SH_CORE_ERROR("Could not read from file '{0}'", path);
        } else {
            contents.resize(size);
            fs.seekg(0, std::ios::beg);
            fs.read(&contents[0], size);
            fs.close();

            return contents;
        }
    } else {
        SH_CORE_ERROR("Could not open file '{0}'", path);
    }

    return "";
}

Font::Font(const std::string &path, int fontSize)
    : mSize(fontSize) {
    auto fontData = readFile(path);

    // Font info
//    stbtt_InitFont(&mFontInfo, reinterpret_cast<const unsigned char *>(fontData.c_str()), 0);
//    scale = stbtt_ScaleForPixelHeight(&mFontInfo, mSize);
//    SH_CORE_WARN("Scale: {0}, {1}", scale);
//    int StbAscent;
//    int StbDescent;
//    int StbLineGap;
//    stbtt_GetFontVMetrics(&info, &StbAscent, &StbDescent, &StbLineGap);
//    ascent = StbAscent * scale;
//    descent = StbDescent * scale;
//    lineGap = StbLineGap * scale;
//    lineAdvance = ascent - descent + lineGap;

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

}