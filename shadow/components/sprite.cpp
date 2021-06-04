#include "sprite.h"

namespace Shadow {
    void Sprite::Draw() {
        glm::vec4 box = { mPosition.x, mPosition.y,
                          mPosition.x + mSize.x, mPosition.y + mSize.y };

        Render::DrawRect(box, mPosition.z, mTexture.GetTexture(), mTexture.GetTexCoords(),
                         mRotation, mFlipX, mFlipY, mTint);
    }

}