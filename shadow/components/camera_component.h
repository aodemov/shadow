#pragma once

#include "shadow/ecs/component.h"
#include "shadow/renderer/camera_controller.h"

namespace Shadow {
class CameraComponent {
public:
    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    explicit CameraComponent(CameraController controller)
    : cameraController(controller) {}

    CameraController cameraController;
};
}
