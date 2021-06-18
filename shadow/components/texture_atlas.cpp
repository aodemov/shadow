#include "texture_atlas.h"

namespace Shadow {
TextureAtlas::TextureAtlas(Ref<Texture> const& texture, std::initializer_list<AtlasTile> tiles) {
    for (auto& tile : tiles) {
        mTiles.emplace(tile.id, SubTexture(texture, tile.offset, tile.size));
    }
}
}