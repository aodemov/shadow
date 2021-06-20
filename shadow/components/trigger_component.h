#pragma once

namespace Shadow {
class Entity;
class TriggerComponent {
public:
    TriggerComponent() = default;
    TriggerComponent(const TriggerComponent&) = default;
    explicit TriggerComponent(glm::vec4 box)
            : Box(box) {}

    glm::vec4 Box{0.0f};
    std::vector<Entity> Hits{};
};
}
