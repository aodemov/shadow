#pragma once

#include "shadow/ecs/component.h"

namespace Shadow {
class ColliderComponent {
public:
    ColliderComponent() = default;
    ColliderComponent(const ColliderComponent&) = default;
    explicit ColliderComponent(glm::vec4 box)
    : Box(box) {}

    glm::vec4 Box{0.0f};
    bool IsTouching = false;
};
}
