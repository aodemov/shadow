#pragma once

#include <glm/glm.hpp>

namespace Shadow {

class Camera {
public:
    Camera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);

    const glm::vec3& GetPosition() const { return mPosition; }
    void SetPosition(const glm::vec3& pos) { mPosition = pos; Recalculate(); }

    void SetRotation(float rotation) { mRotation = rotation; Recalculate(); }
    float GetRotation() const { return mRotation; }

    const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; };
private:
    void Recalculate();


    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mViewProjectionMatrix;

    glm::vec3 mPosition;
    float mRotation = 0.0f;
};

}
