#pragma once

#include "shadow/renderer/camera.h"

namespace Shadow {
class CameraController {
public:
    CameraController();
    ~CameraController() = default;

    glm::vec3 const& GetPosition() const;
    void SetPosition(glm::vec3 const& pos);

    float GetZoom() const;
    void SetZoom(float zoom);

    float GetRotation() const;
    void SetRotation(float rotation);

    Camera& GetCamera();
    void Recalculate();
private:

    Camera mCamera;

    float mAspectRatio;
    float mZoom;
};
}
