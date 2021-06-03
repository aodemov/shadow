#include "camera_controller.h"

#include "shadow/application/application.h"

namespace Shadow {

CameraController::CameraController()
    : mAspectRatio(1.0f),
      mZoom(1.0f),
      mCamera(0, 0, 0, 0)
{
    Recalculate();
}

void CameraController::Recalculate() {
    mAspectRatio = Application::GetWindow().GetAspectRatio();
    mCamera.SetProjection(-mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom);
}

glm::vec3 const &CameraController::GetPosition() const {
    return mCamera.GetPosition();
}

void CameraController::SetPosition(const glm::vec3 &pos) {
    mCamera.SetPosition(pos);
}

float CameraController::GetZoom() const {
    return mZoom;
}

void CameraController::SetZoom(float z) {
    mZoom = z;
    Recalculate();
}

float CameraController::GetRotation() const {
    return mCamera.GetRotation();
}

void CameraController::SetRotation(float rotation) {
    mCamera.SetRotation(rotation);
}

Camera& CameraController::GetCamera() {
    return mCamera;
}

}
