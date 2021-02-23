#pragma once

#include <vector>

#include "shadow/shadow.h"

using namespace Shadow;

class Snake {
public:
    enum class Direction : uint8_t {
        Up = 0,
        Left,
        Down,
        Right
    };

    Snake();

    void Update(float delta);
    void SetDirection(Direction d);
    void Feed(float amount);

    std::vector<glm::vec2> const& GetBody() { return body; }

private:
    std::vector<glm::vec2> body;
    Direction direction;
    Direction newDirection;
    float toAdd = 0;
    float speed;
};
