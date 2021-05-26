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

Font::Font(const std::string &path) {
    auto fontData = readFile(path);
    auto atlasData = std::make_unique<uint8_t[]>(atlasWidth * atlasHeight);

    charInfo = std::make_unique<stbtt_packedchar[]>(charCount);

    stbtt_pack_context context;
    if (!stbtt_PackBegin(&context, atlasData.get(), atlasWidth, atlasHeight, 0, 1, nullptr))
        SH_CORE_ERROR("Failed to initialize font");

    stbtt_PackSetOversampling(&context, oversampleX, oversampleY);
    if (!stbtt_PackFontRange(&context, reinterpret_cast<const unsigned char *>(fontData.c_str()), 0,
                             size, firstChar, charCount, charInfo.get()))
        SH_CORE_ERROR("Failed to pack font");

    stbtt_PackEnd(&context);

    stbtt_InitFont(&info, reinterpret_cast<const unsigned char *>(fontData.c_str()), 0);
    scale = stbtt_ScaleForPixelHeight(&info, size);
    SH_INFO("Scale: {0}", scale);

    uint32_t tid;
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, atlasData.get());
    glGenerateMipmap(GL_TEXTURE_2D);

    mTexture = MakeRef<SubTexture>(MakeRef<Texture>(atlasWidth, atlasHeight, tid));
}

stbtt_aligned_quad Font::GetTexCoords(uint32_t c, glm::vec2* offset) {
    stbtt_aligned_quad quad;

    stbtt_GetPackedQuad(charInfo.get(), atlasWidth, atlasHeight,
                        c - firstChar, &offset->x, &offset->y, &quad, 0);

//    int ax;
//    int lsb;
//    stbtt_GetCodepointHMetrics(&info, c, &ax, &lsb);
//    res.texCoords = { quad.s0, quad.t1, quad.s1, quad.t0 };

    float height = quad.y0 - quad.y1;
    quad.y0 -= 2 * height;


    return quad;
}

}