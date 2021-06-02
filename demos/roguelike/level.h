#pragma once

#include "shadow/shadow.h"

using namespace Shadow;

class Level {
public:
    void Load();
    void Update(float delta);
    void Draw();

private:
    std::vector<Sprite> mTiles{};
    std::vector<AnimatedSprite> mObjects{};
};
