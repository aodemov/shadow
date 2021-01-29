#include "render.h"

#include <glad/gl.h>

namespace Shadow {

Render::SceneData* Render::sceneData = new SceneData;

void Render::BeginScene(Camera& camera) {
    sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Render::EndScene() {

}

void Render::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> &vertexArray) {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);

    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Render::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}