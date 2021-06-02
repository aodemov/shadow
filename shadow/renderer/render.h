#pragma once

#include <glm/glm.hpp>

#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/shader.h"
#include "shadow/renderer/camera.h"
#include "shadow/renderer/texture.h"
#include "shadow/renderer/sub_texture.h"
#include "shadow/renderer/font.h"

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

    static void DrawRect(glm::vec4 const& box, glm::vec4 const& color);
    static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color, float rotation = 0.0f);

    static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, Ref<Texture> const& texture, float rotation = 0.0f);
    static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, SubTexture const& subTexture, float rotation = 0.0f);

    static void DrawRect(glm::vec4 const& box, float z, Ref<Texture> const& texture, glm::vec4 const& texCoords,
                         float rotation = 0.0f, bool flipX = false, bool flipY = false,
                         glm::vec4 const& color = { 1.0f, 1.0f, 1.0f, 1.0f });

    static void DrawLine(glm::vec2 const& from, glm::vec2 const& to, float width, glm::vec4 color);

    static void DrawText(std::string const&  text, glm::vec3 const& position, const Ref<Font>& font, glm::vec4 color);
private:
    static void UseShader(Shader* shader);
};

}