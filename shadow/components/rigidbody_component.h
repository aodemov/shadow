#pragma once

#include "shadow/ecs/component.h"

namespace Shadow {
class RigidbodyComponent {
public:
    RigidbodyComponent() = default;
    RigidbodyComponent(const RigidbodyComponent&) = default;
    explicit RigidbodyComponent(glm::vec2 velocity)
    : Velocity(velocity) {}

    glm::vec2 Velocity{0.0f};
};
}
