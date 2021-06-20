#include "render.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <shadow/application/game_loop.h>
#include <shadow/application/application.h>

#include "lib/stb_truetype/stb_truetype.h"


namespace Shadow {

struct RectVertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TexIndex;
    float TilingFactor;
};

struct RenderData {
    static inline const uint32_t MaxRects = 10000;
    static inline const uint32_t MaxVertices = MaxRects * 4;
    static inline const uint32_t MaxIndices = MaxRects * 6;
    static inline const uint32_t MaxTextureSlots = 16;

    Scope<Shader> DefaultShader;
    Scope<Shader> FontShader;
    Shader* CurrentShader = nullptr;

    Ref<VertexArray> RectVA;
    RectVertex* RectVertexBuffer = nullptr;

    std::array<Ref<Texture>, MaxTextureSlots> TextureSlots;

    uint32_t RectCount = 0;
    uint32_t TextureSlot = 1;
    RectVertex* RectVertexBufferPtr = nullptr;
};

static RenderData* renderData;


void Render::Init() {
    // OpenGL Options
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    renderData = new RenderData;
    // Preparing rect vertex data
    renderData->RectVA = MakeRef<VertexArray>();

    auto rectVB = MakeRef<VertexBuffer>(RenderData::MaxVertices * sizeof(RectVertex));
    rectVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoords" },
            { ShaderDataType::Float,  "a_TexIndex" },
            { ShaderDataType::Float,  "a_TilingFactor" },
    });
    renderData->RectVA->AddVertexBuffer(rectVB);

    renderData->RectVertexBuffer = new RectVertex[RenderData::MaxVertices];
    renderData->RectVertexBufferPtr = renderData->RectVertexBuffer;

    // Generating indices for rects
    auto* rectIndices = new uint32_t[+RenderData::MaxIndices];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < RenderData::MaxIndices; i += 6) {
        rectIndices[i + 0] = offset + 0;
        rectIndices[i + 1] = offset + 1;
        rectIndices[i + 2] = offset + 2;
        rectIndices[i + 3] = offset + 2;
        rectIndices[i + 4] = offset + 3;
        rectIndices[i + 5] = offset + 0;

        offset += 4;
    }
    auto rectIB = MakeRef<IndexBuffer>(rectIndices, RenderData::MaxIndices);
    renderData->RectVA->SetIndexBuffer(rectIB);
    delete[] rectIndices;

    // Compiling shaders
    renderData->DefaultShader = MakeScope<Shader>("assets/shaders/Default.glsl");
    renderData->FontShader = MakeScope<Shader>("assets/shaders/Font.glsl");
    renderData->DefaultShader->Bind();

    // Uploading sampler2d array data to Default shader
    int32_t samplers[RenderData::MaxTextureSlots];
    for (int i = 0; i < RenderData::MaxTextureSlots; i++)
        samplers[i] = i;

    renderData->DefaultShader->UploadUniformIntArray("u_Textures", samplers, RenderData::MaxTextureSlots);

    renderData->FontShader->Bind();
    renderData->FontShader->UploadUniformIntArray("u_Textures", samplers, RenderData::MaxTextureSlots);

    renderData->CurrentShader = renderData->DefaultShader.get();

    // Generating 1x1 white texture for colored rects
    renderData->TextureSlots[0] = Texture::CreateWhiteTexture();

#ifdef SH_DEBUGGER
    Debugger::Stats.MaxRects = RenderData::MaxRects;
    Debugger::Stats.MaxTextureSlots = RenderData::MaxTextureSlots;
#endif
}

void Render::Shutdown() {
    delete[] renderData->RectVertexBuffer;
    delete renderData;
}

void Render::BeginScene(Camera& camera) {
    // Uploading ViewProjection matrix to Default shader
    renderData->DefaultShader->Bind();
    renderData->DefaultShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    renderData->FontShader->Bind();
    renderData->FontShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    UseShader(renderData->DefaultShader.get());
}

void Render::EndScene() {
    Flush();
}

void Render::Flush() {
    renderData->CurrentShader->Bind();

    // Binding all textures to corresponding texture slots
    for (uint32_t i = 0; i < renderData->TextureSlot; i++) {
        renderData->TextureSlots[i]->Bind(i);
    }

    // Uploading vertex data to GPU
    renderData->RectVA->GetVertexBuffers()[0]->SetData((const void*)renderData->RectVertexBuffer,
                                                      (renderData->RectVertexBufferPtr - renderData->RectVertexBuffer) * sizeof(RectVertex));

    renderData->RectVA->Bind();
    glDrawElements(GL_TRIANGLES, (int)renderData->RectCount * 6, GL_UNSIGNED_INT, nullptr);


#ifdef SH_DEBUGGER
    Debugger::Stats.DrawCalls++;
    Debugger::Stats.RectCount += renderData->RectCount;
    Debugger::Stats.TextureCount = renderData->TextureSlot;
#endif

    // Resetting iterators
    renderData->RectVertexBufferPtr = renderData->RectVertexBuffer;
    renderData->RectCount = 0;
    renderData->TextureSlot = 1;
}

void Render::UseShader(Shader *shader) {
    if (shader != nullptr && !(*renderData->CurrentShader == *shader)) {
        Flush();
        renderData->CurrentShader = shader;
    }
}

void Render::DrawRect(const glm::vec4 &box, const glm::vec4 &color) {
    if (renderData->RectCount >= RenderData::MaxRects)
        Flush();

    const float textureIndex = 0.0f;
    const float tilingFactor = 1.0f;


    renderData->RectVertexBufferPtr->Position = glm::vec3{ box.x, box.y, 0.8f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { 0, 0 };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = glm::vec3{ box.z, box.y, 0.8f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { 1, 0 };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = glm::vec3{ box.z, box.w, 0.8f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { 1, 1 };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = glm::vec3{ box.x, box.w, 0.8f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { 0, 1 };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectCount++;
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation) {
    UseShader(renderData->DefaultShader.get());

    if (renderData->RectCount >= RenderData::MaxRects)
        Flush();

    const float texIndex = 0.0f;
    const float tilingFactor = 1.0f;

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(-rotation), { 0.0f, 0.0f, 1.0f }) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{-0.5f, -0.5f, 1.0f, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = {0.0f, 0.0f };
    renderData->RectVertexBufferPtr->TexIndex = texIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{0.5f, -0.5f, 1.0f, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = {1.0f, 0.0f };
    renderData->RectVertexBufferPtr->TexIndex = texIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{0.5f, 0.5f, 1.0f, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = {1.0f, 1.0f };
    renderData->RectVertexBufferPtr->TexIndex = texIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{-0.5f, 0.5f, 1.0f, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = {0.0f, 1.0f };
    renderData->RectVertexBufferPtr->TexIndex = texIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectCount++;
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const SubTexture &subTexture,
                      float rotation) {
    UseShader(renderData->DefaultShader.get());


//    glm::vec2 halfSize = size / 2.0f;
    glm::vec4 box = { position.x, position.y, position.x + size.x, position.y + size.y };

    DrawRect(box, position.z, subTexture.GetTexture(), subTexture.GetTexCoords(),  rotation);
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture> &texture, float rotation) {
    UseShader(renderData->DefaultShader.get());

//    glm::vec2 halfSize = size / 2.0f;
    glm::vec4 box = { position.x, position.y, position.x + size.x, position.y + size.y };

    DrawRect(box, position.z, texture, { 0.0f, 0.0f, 1.0f, 1.0f }, rotation);
}

void Render::DrawRect(const glm::vec4 &box, float z, const Ref<Texture> &texture, const glm::vec4 &texCoords,
                      float rotation, bool flipX, bool flipY,
                      glm::vec4 const& color) {
    if (renderData->RectCount >= RenderData::MaxRects)
        Flush();

    const float tilingFactor = 1.0f;

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < renderData->TextureSlot; i++) {
        if (renderData->TextureSlots[i] == texture) {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f) {
        if (renderData->TextureSlot >= RenderData::MaxTextureSlots)
            Flush();

        textureIndex = (float)renderData->TextureSlot;
        renderData->TextureSlots[renderData->TextureSlot] = texture;
        renderData->TextureSlot++;
    }

    glm::mat4 transform(1.0f);
    if (rotation != 0.0f) {
        glm::vec2 halfSize = glm::vec2{ box.z - box.x, box.w - box.y } / 2.0f;
        glm::vec3 origin = { box.x + halfSize.x, box.y + halfSize.y, 0.0f };

        transform = glm::translate(glm::mat4(1.0f), origin) *
                    glm::rotate(glm::mat4(1.0f), glm::radians(-rotation), { 0.0f, 0.0f, 1.0f }) *
                    glm::translate(glm::mat4(1.0f), -origin);
    }

    glm::vec4 tc = texCoords;
    if (flipX)
        std::swap(tc.x, tc.z);
    if (flipY)
        std::swap(tc.y, tc.w);


    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{ box.x, box.y, z, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { tc.x, tc.y };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{ box.z, box.y, z, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { tc.z, tc.y };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{ box.z, box.w, z, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { tc.z, tc.w };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectVertexBufferPtr->Position = transform * glm::vec4{ box.x, box.w, z, 1.0f };
    renderData->RectVertexBufferPtr->Color = color;
    renderData->RectVertexBufferPtr->TexCoords = { tc.x, tc.w };
    renderData->RectVertexBufferPtr->TexIndex = textureIndex;
    renderData->RectVertexBufferPtr->TilingFactor = tilingFactor;
    renderData->RectVertexBufferPtr++;

    renderData->RectCount++;
}

void Render::DrawLine(const glm::vec2 &from, const glm::vec2 &to, float width, glm::vec4 color) {
    glm::vec3 pos = { (from.x + to.x) / 2, (from.y + to.y) / 2, 0.0f };
    glm::vec2 size = { fabs(from.x - to.x) + width, fabs(from.y - to.y) + width };

    DrawRect(pos, size, color);
}

void Render::DrawText(const std::string &text, const glm::vec3 &position, const Ref<Font>& font, glm::vec4 color) {
    UseShader(renderData->FontShader.get());

    glm::vec2 offset = { 0, 0 };
    for (auto c : text) {
        auto g = font->GetTexCoords(c, &offset);

//        glm::vec2 scale = { 2.0f / Application::GetWindow().GetHeight(), 2.0f / Application::GetWindow().GetHeight() };
        glm::vec2 scale = {1, -1};
        glm::vec4 box = { position.x + g.x0 * scale.x, position.y + g.y0 * scale.y, position.x + g.x1 * scale.x, position.y + g.y1 * scale.y };
        glm::vec4 texCoords = { g.s0, g.t0, g.s1, g.t1 };

        DrawRect(box, position.z, font->GetTexture(), texCoords, 0.0f, false, false, color);
    }
}




void Render::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Render::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


}