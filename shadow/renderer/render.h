#pragma once

#include <glm/glm.hpp>

#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/shader.h"
#include "shadow/renderer/camera.h"
#include "shadow/renderer/texture.h"
#include "shadow/renderer/sub_texture.h"

namespace Shadow {

class Render {
public:
    static void Init();
    static void Shutdown();

    static void BeginScene(Camera& camera);
    static void EndScene();
    static void Flush();

    static void SetClearColor(glm::vec4 const& color);
    static void Clear();

    static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color, float rotation = 0.0f);
    static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, Ref<SubTexture> const& texture, float rotation = 0.0f);

    static void DrawLine(glm::vec2 const& from, glm::vec2 const& to, float width, glm::vec4 color);
};

}