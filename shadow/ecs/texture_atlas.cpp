#include "texture_atlas.h"

namespace Shadow {
TextureAtlas::TextureAtlas(Ref<Texture> texture, std::initializer_list<AtlasTile> tiles) {
    mTiles.reserve(tiles.size());
    for (auto& tile : tiles) {
        mTiles.push_back(MakeRef<SubTexture>(texture, tile.offset, tile.size));
    }
}
}