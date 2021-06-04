#include "animated_sprite.h"

#include "shadow/renderer/render.h"

namespace Shadow {
void AnimatedSprite::Draw() {
    glm::vec4 box = { mPosition.x, mPosition.y,
                      mPosition.x + mSize.x, mPosition.y + mSize.y };

    // TODO refactor
    Render::DrawRect(box, mPosition.z, mAnimationController.GetAnimation().GetTexture().GetTexture(),
                     mAnimationController.GetAnimation().GetTexture().GetTexCoords(),
                     mRotation, mFlipX, mFlipY, mTint);
}

void AnimatedSprite::Update(float delta) {
    mAnimationController.Update(delta);
}
}