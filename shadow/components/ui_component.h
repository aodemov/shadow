#pragma once

#include "shadow/ecs/component.h"
#include "shadow/ui/ui_container.h"

namespace Shadow {
class UiComponent {
public:
    UiComponent() = default;
    UiComponent(const UiComponent&) = default;
    explicit UiComponent(const UiContainer& container)
    : Container(container) {}

    UiContainer Container;
};
}
