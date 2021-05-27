#pragma once

#include <vector>

#include "shadow/shadow.h"

class Snake {
public:
    enum class Direction : uint8_t {
        Up = 0,
        Left,
        Down,
        Right
    };

    std::vector<glm::vec2> const& GetBody() { return body; }
    float GetLength() const { return length; }

    Snake();

    void SetDirection(Direction d);
    void Feed(float amount);

    void Update(float delta);
    void Draw();

private:
    std::vector<glm::vec2> body;
    Direction direction;
    Direction newDirection;
    float toAdd = 0;
    float speed;

    float length = 0;
};
