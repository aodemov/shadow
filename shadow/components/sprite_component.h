#pragma once

#include "shadow/ecs/component.h"
#include "shadow/components/sprite.h"

namespace Shadow {
class SpriteComponent {
public:
    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = default;
    explicit SpriteComponent(Sprite sprite)
        : sprite(std::move(sprite)) {}

    Sprite sprite;
};
}
