#pragma once

#include <shadow/shadow.h>

using namespace Shadow;

class Player {
public:
    void Load();
    void Update(float delta);
    void Draw();

    glm::vec3 const& GetPosition() { return mSprite->Position(); }

private:
    Scope<AnimatedSprite> mSprite;

    float mSpeed = 5;
};

