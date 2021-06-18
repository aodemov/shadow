#include "collision.h"


namespace Shadow {
bool Collision::Aabb(glm::vec4 box1, glm::vec4 box2) {
    if (box1.x < box2.z &&
        box1.z > box2.x &&
        box1.y < box2.w &&
        box1.w > box2.y) {
        return true;
    }

    return false;
}

glm::vec2 Collision::AabbDistance(glm::vec4 box1, glm::vec4 box2) {
    float dx = 0;
    float dy = 0;

    if (box1.x < box2.x)
    {
        dx = box2.x - (box1.z);
    }
    else if (box1.x > box2.x)
    {
        dx = box1.x - (box2.z);
    }

    if (box1.y < box2.y)
    {
        dy = box2.y - (box1.w);
    }
    else if (box1.y > box2.y)
    {
        dy = box1.y - (box2.w);
    }

    return glm::vec2{dx, dy};
}
}