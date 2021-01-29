#pragma once

#include <glm/glm.hpp>

#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/shader.h"
#include "shadow/renderer/camera.h"

namespace Shadow {

class Render {
public:
    static void BeginScene(Camera& camera);
    static void EndScene();

    static void Submit(std::shared_ptr<Shader> const& shader, std::shared_ptr<VertexArray> const& vertexArray);

    static void SetClearColor(glm::vec4 const& color);
    static void Clear();

private:
    struct SceneData {
        glm::mat4 viewProjectionMatrix;
    };

    static SceneData* sceneData;
};

}