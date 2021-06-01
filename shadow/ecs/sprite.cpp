#include "sprite.h"

namespace Shadow {
    void Sprite::Draw() {
        Render::DrawRect(mPosition, mSize, mTexture, mRotation);
    }

}