#pragma once

#include "shadow/shadow.h"

#include <vector>

class Food {
public:
    struct FoodPiece {
        glm::vec2 position;
        float value;
    };

    Food(float width, float height)
        : width(width),
          height(height)
    {}

    std::vector<FoodPiece>& GetPieces() { return pieces; }

    void Generate(int amount = 1);

    void Draw();

private:
    float width, height;

    std::vector<FoodPiece> pieces;
};
