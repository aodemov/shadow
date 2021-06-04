#pragma once

#include <shadow/shadow.h>

using namespace Shadow;

class Player : public GameObject {
public:
    void OnLoad() override;
    void VariableUpdate(float delta) override;

    glm::vec3 const& GetPosition() { return mSprite->Position(); }

private:
    Scope<AnimatedSprite> mSprite;

    float mSpeed = 5;
};

