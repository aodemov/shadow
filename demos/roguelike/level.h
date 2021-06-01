#pragma once

#include "shadow/shadow.h"

using namespace Shadow;

class Level {
public:
    void Load();
    void Draw();

private:
    std::vector<Sprite> mTiles;
};
