#include "food.h"

#include <cstdlib>

using namespace Shadow;

float randomFloat(float lo, float hi) {
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}


void Food::Generate(int amount) {
    srand(time(NULL));
    while (amount--) {
        FoodPiece p;
        p.position = { randomFloat(-width / 2, width / 2), randomFloat(-height / 2, height / 2)};
        p.value = (rand() % 5 + 1) * 0.2f;

        SH_INFO("Generated food: {0}:{1} ({2})", p.position.x, p.position.y, p.value);

        pieces.emplace_back(p);
    }
}

void Food::Draw() {
    const float foodSize = 0.3f;
    for (auto& p : pieces) {
        glm::vec4 color = { 1.0f, 0, 0, 0.8f};
        Render::DrawRect({p.position, 0.0f}, (float)sqrt(p.value) * glm::vec2(foodSize, foodSize), color, 45.0f);
    }
}
