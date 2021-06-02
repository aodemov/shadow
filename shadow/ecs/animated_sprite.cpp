#include "animated_sprite.h"

#include "shadow/renderer/render.h"

namespace Shadow {
void AnimatedSprite::Draw() {
    glm::vec2 halfSize = mSize / 2.0f;
    glm::vec4 box = { mPosition.x - halfSize.x, mPosition.y - halfSize.y,
                      mPosition.x + halfSize.x, mPosition.y + halfSize.y };

    Render::DrawRect(box, mPosition.z, mAnimation.GetTexture().GetTexture(), mAnimation.GetTexture().GetTexCoords(),
                     mRotation, mFlipX, mFlipY, mTint);
}

void AnimatedSprite::Update(float delta) {
    mAnimation.Update(delta);
}
}