#include "snake.h"

using namespace Shadow;

Snake::Snake()
    : body(),
      direction(Direction::Right),
      newDirection(Direction::Right),
      speed(3.5f)
{
    body.emplace_back(glm::vec2(0, 0));
    body.emplace_back(glm::vec2(-2, 0));
}

void Snake::Update(float delta) {
    float distance = speed * delta;

    if (newDirection != direction) {
        body.insert(body.begin(), {body[0]});
        direction = newDirection;
    }

    if(direction == Direction::Left) {
        body[0].x -= distance;
    } else if (direction == Direction::Right) {
        body[0].x += distance;
    } else if (direction == Direction::Up) {
        body[0].y += distance;
    } else if (direction == Direction::Down) {
        body[0].y -= distance;
    }

    glm::vec2 segment = body[body.size()-2] - body[body.size()-1];

    if (toAdd > distance) {
        toAdd -= distance;
        distance = 0;
    } else {
        distance -= toAdd;
        toAdd = 0;
    }

    float length = glm::length(segment);
    if (length < distance) {
        distance -= length;
        body.erase(body.end() - 1);

        segment = body[body.size()-2] - body[body.size()-1];
    }

    body[body.size()-1] = body[body.size()-1] + glm::normalize(segment) * distance;
}

void Snake::Draw() {
    float snakeWidth = 0.2f;
    for (int i = 0; i < body.size() - 1; i++) {
        glm::vec4 color = { 52.0f / 256, 235.0f / 256, 161.0f / 256, 0.8f };
        Render::DrawLine(body[i], body[i+1], snakeWidth, color);
    }
}

void Snake::SetDirection(Direction d) {
    if (d == direction || ((uint8_t)d % 2) == ((uint8_t)direction % 2))
        return;

    newDirection = d;
}

void Snake::Feed(float amount) {
    toAdd += amount;
    length += amount;
}

