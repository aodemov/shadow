#pragma once

#include <glm/glm.hpp>

namespace Shadow {

class Camera {
public:
    Camera(float left, float right, float bottom, float top);

    const glm::vec3& GetPosition() const { return position; }
    void SetPosition(const glm::vec3& pos) { position = pos; Recalculate(); }

    void SetRotation(float rot) { rotation = rot; Recalculate(); }
    float GetRotation() const { return rotation; }

    const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return viewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; };
private:
    void Recalculate();


    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 viewProjectionMatrix;

    glm::vec3 position;
    float rotation = 0.0f;
};

}
