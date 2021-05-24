#include "render.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <shadow/application/game_loop.h>

namespace Shadow {

struct RectVertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TexIndex;
};

struct SceneData {
    std::shared_ptr<Shader> colorShader;
    std::shared_ptr<Shader> textureShader;
    std::shared_ptr<Shader> geometryShader;

    std::shared_ptr<Texture> whiteTexture;

    static inline const uint32_t maxRects = 10000;
    static inline const uint32_t maxVertices = maxRects * 4;
    static inline const uint32_t maxIndices = maxRects * 6;
    static inline const uint32_t maxTextureSlots = 16;

    std::shared_ptr<VertexArray> rectVA;

    uint32_t rectCount = 0;

    RectVertex* rectVertexBuffer = nullptr;
    RectVertex* rectVertexBufferPtr = nullptr;
};

static SceneData sceneData;


void Render::Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    sceneData.rectVA = std::make_shared<VertexArray>();

    auto rectVB = std::make_shared<VertexBuffer>(sceneData.maxVertices * sizeof(RectVertex));
    rectVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoords" },
            { ShaderDataType::Float,  "a_TexIndex" },
    });
    sceneData.rectVA->AddVertexBuffer(rectVB);

    sceneData.rectVertexBuffer = new RectVertex[sceneData.maxVertices];

    uint32_t* rectIndices = new uint32_t[+sceneData.maxIndices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < sceneData.maxIndices; i += 6) {
        rectIndices[i + 0] = offset + 0;
        rectIndices[i + 1] = offset + 1;
        rectIndices[i + 2] = offset + 2;
        rectIndices[i + 3] = offset + 2;
        rectIndices[i + 4] = offset + 3;
        rectIndices[i + 5] = offset + 0;

        offset += 4;
    }

    auto rectIB = std::make_shared<IndexBuffer>(rectIndices, sceneData.maxIndices);
    sceneData.rectVA->SetIndexBuffer(rectIB);
    delete[] rectIndices;

    sceneData.colorShader = std::make_shared<Shader>("assets/shaders/Color.glsl");
    sceneData.textureShader = std::make_shared<Shader>("assets/shaders/Texture.glsl");
    sceneData.geometryShader = std::make_shared<Shader>("assets/shaders/Geometry.glsl");
    sceneData.textureShader->Bind();
    sceneData.textureShader->UploadUniformInt("u_Texture", 0);
    sceneData.whiteTexture = Texture::CreateWhiteTexture();
}

void Render::Shutdown() {
    delete[] sceneData.rectVertexBuffer;
}

void Render::BeginScene(Camera& camera) {
//    sceneData.colorShader->Bind();
//    sceneData.colorShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
//    sceneData.geometryShader->Bind();
//    sceneData.geometryShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    sceneData.whiteTexture->Bind();
    sceneData.textureShader->Bind();
    sceneData.textureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    sceneData.rectVertexBufferPtr = sceneData.rectVertexBuffer;
    sceneData.rectCount = 0;
}

void Render::EndScene() {
    Flush();
}

void Render::Flush() {
    sceneData.rectVA->GetVertexBuffers()[0]->SetData((const void*)sceneData.rectVertexBuffer,
                                                     (sceneData.rectVertexBufferPtr - sceneData.rectVertexBuffer) * sizeof(RectVertex));

    sceneData.rectVA->Bind();
    glDrawElements(GL_TRIANGLES, sceneData.rectCount * 6, GL_UNSIGNED_INT, nullptr);
}

void Render::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Render::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation) {
    sceneData.rectVertexBufferPtr->Position = position;
    sceneData.rectVertexBufferPtr->Color = color;
    sceneData.rectVertexBufferPtr->TexCoords = { 0.0f, 0.0f };
    sceneData.rectVertexBufferPtr->TexIndex = 0;
    sceneData.rectVertexBufferPtr++;

    sceneData.rectVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
    sceneData.rectVertexBufferPtr->Color = color;
    sceneData.rectVertexBufferPtr->TexCoords = { 1.0f, 0.0f };
    sceneData.rectVertexBufferPtr->TexIndex = 0;
    sceneData.rectVertexBufferPtr++;

    sceneData.rectVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
    sceneData.rectVertexBufferPtr->Color = color;
    sceneData.rectVertexBufferPtr->TexCoords = { 1.0f, 1.0f };
    sceneData.rectVertexBufferPtr->TexIndex = 0;
    sceneData.rectVertexBufferPtr++;

    sceneData.rectVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
    sceneData.rectVertexBufferPtr->Color = color;
    sceneData.rectVertexBufferPtr->TexCoords = { 0.0f, 1.0f };
    sceneData.rectVertexBufferPtr->TexIndex = 0;
    sceneData.rectVertexBufferPtr++;

    sceneData.rectCount++;
}

void Render::DrawRect(glm::vec3 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float rotation) {
//    sceneData.textureShader->Bind();
//
//    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
//                          * glm::rotate(glm::mat4(1.0f), glm::radians(-rotation), { 0.0f, 0.0f, 1.0f })
//                          * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
//
//    sceneData.textureShader->UploadUniformMat4("u_Transform", transform);
//
//    texture->Bind();
//
//    sceneData.rectVertexArray->Bind();
//    glDrawElements(GL_TRIANGLES, sceneData.rectVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::DrawLine(const glm::vec2 &from, const glm::vec2 &to, float width, glm::vec4 color) {
    glm::vec3 pos = { (from.x + to.x) / 2, (from.y + to.y) / 2, 0.0f };
    glm::vec2 size = { fabs(from.x - to.x) + width, fabs(from.y - to.y) + width };

    DrawRect(pos, size, color);
}

void Render::TestLine() {
    float lineVertices[4 * 7] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
    };

//    glm::vec4 p0(-1.0f, -1.0f, 0.0f, 1.0f);
//    glm::vec4 p1(1.0f, -1.0f, 0.0f, 1.0f);
//    glm::vec4 p2(1.0f, 1.0f, 0.0f, 1.0f);
//    glm::vec4 p3(-1.0f, 1.0f, 0.0f, 1.0f);
//    std::vector<glm::vec4> varray1{ p3, p0, p1, p2, p3, p0, p1 };
//    GLuint ssbo1 = CreateSSBO(varray1);

    auto lineVertexArray = std::make_shared<VertexArray>();

    auto ssbo = std::make_shared<ShaderStorageBuffer>(lineVertices, sizeof(lineVertices));

    uint32_t lineIndices[] = { 3, 0, 1, 2, 3, 0, 1 };
    auto indexBuffer = std::make_shared<IndexBuffer>(lineIndices, sizeof(lineIndices));
    lineVertexArray->SetIndexBuffer(indexBuffer);

    sceneData.geometryShader->Bind();

    sceneData.geometryShader->UploadUniformFloat2("u_resolution", { (float)GameLoop::GetWindow().GetWidth(), (float)GameLoop::GetWindow().GetHeight() });
    sceneData.geometryShader->UploadUniformFloat1("u_thickness", 20.0f);

    ssbo->Bind();
    lineVertexArray->Bind();
//    glDrawElements(GL_TRIANGLES, lineVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
//    glDrawArrays(GL_TRIANGLES, 0, 6 * (4));
}


}