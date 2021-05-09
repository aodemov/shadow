#include "sprite.h"

namespace Shadow {
    void Sprite::Draw() {
        Render::DrawRect(_position, _size, _texture, _rotation);
    }

}