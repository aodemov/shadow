#include "sprite.h"

namespace Shadow {
    void Sprite::Draw() {
        glm::vec2 halfSize = mSize / 2.0f;
        glm::vec4 box = { mPosition.x - halfSize.x, mPosition.y - halfSize.y,
                          mPosition.x + halfSize.x, mPosition.y + halfSize.y };

        Render::DrawRect(box, mPosition.z, mTexture.GetTexture(), mTexture.GetTexCoords(),
                         mRotation, mFlipX, mFlipY, mTint);
    }

}