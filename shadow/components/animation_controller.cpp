#include "animation_controller.h"

namespace Shadow {
AnimationController::AnimationController(std::initializer_list<std::pair<std::string, const Animation &>> states,
                                         const std::string &defaultAnimation)
{
    mStates.reserve(states.size());
    mCurrentAnimation = mStates.begin();
    for (auto& state : states) {
        mStates.emplace_back(state.first, state.second);
    }

    std::sort(mStates.begin(), mStates.end(), [](const auto &a, const auto &b) { return a.first < b.first; });

    SetState(defaultAnimation);
}

void AnimationController::Update(float delta) {
    mCurrentAnimation->second.Update(delta);
}

void AnimationController::SetState(const std::string &state)  {
    if (mCurrentAnimation->first == state)
        return;

    auto it = std::lower_bound(mStates.begin(), mStates.end(), state, compareAnimationState());

    if (it != mStates.end()) {
        mCurrentAnimation = it;
    } else {
        SH_CORE_ERROR("Animation state \"{0}\" not found!", state);
        mCurrentAnimation = mStates.begin();
    }
}
}