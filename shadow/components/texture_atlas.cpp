#include "texture_atlas.h"

namespace Shadow {
TextureAtlas::TextureAtlas(Ref<Texture> const& texture, std::initializer_list<AtlasTile> tiles) {
    mTiles.reserve(tiles.size());
    for (auto& tile : tiles) {
        mTiles.push_back(SubTexture(texture, tile.offset, tile.size));
    }
}
}