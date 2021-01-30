#include "render.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Shadow {

void Render::Init() {
    sceneData = new SceneData;
    sceneData->rectVertexArray = std::make_shared<VertexArray>();

    float rectVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };

    auto vertexBuffer = std::make_shared<VertexBuffer>(rectVertices, sizeof(rectVertices));
    vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
    });
    sceneData->rectVertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
    auto indexBuffer = std::make_shared<IndexBuffer>(rectIndices, sizeof(rectIndices));
    sceneData->rectVertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

    sceneData->rectShader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
}

void Render::Shutdown() {
    delete sceneData;
}

void Render::BeginScene(Camera& camera) {
    sceneData->rectShader->Bind();
    sceneData->rectShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Render::EndScene() {

}

void Render::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Render::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
    sceneData->rectShader->UploadUniformFloat4("u_Color", color);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    sceneData->rectShader->UploadUniformMat4("u_Transform", transform);

    sceneData->rectVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, sceneData->rectVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

}