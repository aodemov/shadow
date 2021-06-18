#pragma once

#include "shadow/ecs/component.h"
#include "shadow/components/animation_controller.h"

namespace Shadow {
class AnimatorComponent {
public:
    AnimatorComponent(const AnimatorComponent&) = default;
    explicit AnimatorComponent(const AnimationController& controller)
    : animationController(controller) {}

    AnimationController animationController;
};
}
