#include "render.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Shadow {

void Render::Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    sceneData = new SceneData;
    sceneData->rectVertexArray = std::make_shared<VertexArray>();

    float rectVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    auto vertexBuffer = std::make_shared<VertexBuffer>(rectVertices, sizeof(rectVertices));
    vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
    });
    sceneData->rectVertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
    auto indexBuffer = std::make_shared<IndexBuffer>(rectIndices, sizeof(rectIndices));
    sceneData->rectVertexArray->SetIndexBuffer(indexBuffer);

    std::string colorVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string colorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

    std::string textureVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

			void main()
			{
                v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string textureFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

    sceneData->colorShader = std::make_shared<Shader>(colorVertexSrc, colorFragmentSrc);
    sceneData->textureShader = std::make_shared<Shader>(textureVertexSrc, textureFragmentSrc);
    sceneData->textureShader->Bind();
    sceneData->textureShader->UploadUniformInt("u_Texture", 0);
}

void Render::Shutdown() {
    delete sceneData;
}

void Render::BeginScene(Camera& camera) {
    sceneData->colorShader->Bind();
    sceneData->colorShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    sceneData->textureShader->Bind();
    sceneData->textureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Render::EndScene() {

}

void Render::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Render::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation) {
    sceneData->colorShader->Bind();
    sceneData->colorShader->UploadUniformFloat4("u_Color", color);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::rotate(glm::mat4(1.0f), glm::radians(-rotation), { 0.0f, 0.0f, 1.0f })
                          * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    sceneData->colorShader->UploadUniformMat4("u_Transform", transform);

    sceneData->rectVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, sceneData->rectVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::DrawRect(glm::vec3 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float rotation) {
    sceneData->textureShader->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::rotate(glm::mat4(1.0f), glm::radians(-rotation), { 0.0f, 0.0f, 1.0f })
                          * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    sceneData->textureShader->UploadUniformMat4("u_Transform", transform);

    texture->Bind();

    sceneData->rectVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, sceneData->rectVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::DrawLine(const glm::vec2 &from, const glm::vec2 &to, float width, glm::vec4 color) {
    glm::vec3 pos = { (from.x + to.x) / 2, (from.y + to.y) / 2, 0.0f };
    glm::vec2 size = { fabs(from.x - to.x) + width, fabs(from.y - to.y) + width };

    DrawRect(pos, size, color);
}


}