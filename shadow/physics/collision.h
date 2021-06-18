#pragma once

namespace Shadow {
class Collision {
public:
    static bool Aabb(glm::vec4 box1, glm::vec4 box2);
    static glm::vec2 AabbDistance(glm::vec4 box1, glm::vec4 box2);
};
}
