#pragma once

#include "shadow/shadow.h"

using namespace Shadow;

class Level : public GameObject {
public:
    void OnLoad() override;
    void VariableUpdate(float delta) override;

private:
    std::vector<Sprite> mTiles{};
    std::vector<AnimatedSprite> mObjects{};
};
