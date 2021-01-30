#include "camera_controller.h"

#include "shadow/application/game_loop.h"

namespace Shadow {

CameraController::CameraController()
    : aspectRatio(1.0f),
      zoom(1.0f),
      camera(0,0,0,0)
{
    aspectRatio = GameLoop::GetWindow().GetAspectRatio();
    Recalculate();

    EventBus::Instance().addListener<WindowResizeEvent>([&](WindowResizeEvent const& e) {
        aspectRatio = GameLoop::GetWindow().GetAspectRatio();
        Recalculate();
    });
}

void CameraController::Recalculate() {
    camera.SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
}

glm::vec3 const &CameraController::GetPosition() const {
    return camera.GetPosition();
}

void CameraController::SetPosition(const glm::vec3 &pos) {
    camera.SetPosition(pos);
}

float CameraController::GetZoom() const {
    return zoom;
}

void CameraController::SetZoom(float z) {
    zoom = z;
    Recalculate();
}

float CameraController::GetRotation() const {
    return camera.GetRotation();
}

void CameraController::SetRotation(float rotation) {
    camera.SetRotation(rotation);
}

Camera& CameraController::GetCamera() {
    return camera;
}

}
