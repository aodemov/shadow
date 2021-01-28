#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Shadow {


Camera::Camera(float left, float right, float bottom, float top)
    : projectionMatrix(glm::ortho(left, right, bottom, top)),
      viewMatrix(1.0f),
      position(0.0f)
{
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::Recalculate() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0,0,1));

    viewMatrix = glm::inverse(transform);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}
}