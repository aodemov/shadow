#pragma once

namespace Shadow {
class Transform {
public:
    Transform() = default;
    Transform(const Transform&) = default;
    explicit Transform(const glm::vec2& position, float rotation = 0, const glm::vec2& scale = { 1.0f, 1.0f })
        : Position(position),
          Rotation(rotation),
          Scale(scale) {}

    glm::vec2 Position { 0.0f, 0.0f };
    float Rotation { 0.0f };
    glm::vec2 Scale { 1.0f, 1.0f };
};
}
