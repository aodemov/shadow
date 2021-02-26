#include "food.h"

#include <cstdlib>

float randomFloat(float lo, float hi) {
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}


void Food::Generate(int amount) {
    srand(time(NULL));
    while (amount--) {
        FoodPiece p;
        p.position = { randomFloat(-width / 2, width / 2), randomFloat(-height / 2, height / 2)};
        p.value = (rand() % 5 + 1) * 0.2f;

        pieces.emplace_back(p);
    }
}
