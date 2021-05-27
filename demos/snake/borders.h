#pragma once

#include "shadow/shadow.h"

#include <vector>

class Borders {
public:
    Borders(float width, float height);

    std::vector<glm::vec2> const& GetCorners() { return borders; }
    glm::vec2 GetDimensions() { return { width, height }; };

    void Draw();
private:
    std::vector<glm::vec2> borders;
    float width, height;
};

