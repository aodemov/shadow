#pragma once

#include "shadow/ecs/animation.h"

struct compareAnimationState {
    bool operator()(const std::pair<std::string, Shadow::Animation> &a, const std::string& b)
    {
        return (a.first < b);
    }
    bool operator()(const std::string& a,const std::pair<std::string, Shadow::Animation>& b)
    {
        return (a < b.first);
    }
};

namespace Shadow {
class AnimationController {
public:
    AnimationController(std::initializer_list<std::pair<std::string, Animation const&>> states, std::string const& defaultAnimation);

    void Update(float delta);
    void SetState(std::string const& state);

    const Animation& GetAnimation() { return mCurrentAnimation->second; }

private:
    std::vector<std::pair<std::string, Animation>> mStates;
    std::vector<std::pair<std::string, Animation>>::iterator mCurrentAnimation;
};
}