#include "animation.h"

namespace Shadow {
Animation::Animation(Ref<Texture> const& texture, std::initializer_list<AnimationElement> frames) {
    mFrames.reserve(frames.size());
    for (auto& frame : frames) {
        mFrames.push_back({SubTexture(texture, frame.offset, frame.size), frame.duration });
    }
}

Animation::Animation(const Ref<Texture> &texture, float duration, std::initializer_list<AnimationTile> tiles) {
    mFrames.reserve(tiles.size());

    float frameDuration = duration / tiles.size();

    for (auto& tile : tiles) {
        mFrames.push_back({SubTexture(texture, tile.offset, tile.size), frameDuration });
    }
}

void Animation::Update(float delta) {
    currentTime += delta;
    if (currentTime > mFrames[currentFrame].duration) {
        currentTime -= mFrames[currentFrame].duration;
        currentFrame++;
        currentFrame %= mFrames.size();
    }
}
}