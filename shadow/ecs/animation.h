#pragma once

#include "shadow/renderer/sub_texture.h"

namespace Shadow {
class Animation {
public:
    struct AnimationTile {
        glm::vec2 offset;
        glm::vec2 size;
    };

    struct AnimationElement {
        glm::vec2 offset;
        glm::vec2 size;
        float duration;
    };

    Animation(Ref<Texture> const& texture, std::initializer_list<AnimationElement> frames);
    Animation(Ref<Texture> const& texture, float duration, std::initializer_list<AnimationTile> tiles);

    void Update(float delta);
    const SubTexture& GetTexture() { return mFrames[currentFrame].texture; }
private:
    struct AnimationFrame {
        SubTexture texture;
        float duration;
    };

    std::vector<AnimationFrame> mFrames;
    float currentTime;
    int currentFrame = 0;
};
}
