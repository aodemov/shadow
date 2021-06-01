#include "level.h"

struct LevelData {
    uint8_t width;
    uint8_t height;
    std::vector<uint16_t> data;
};

std::vector<LevelData> LoadLevelData(std::string const& filePath) {
    std::vector<LevelData> result;

    std::ifstream fs(filePath);
    if (fs.is_open())
    {
        std::string line;
        while(std::getline(fs,line, ';'))
        {
            LevelData level;
            std::stringstream ss(line);

            std::string width, height;
            std::getline(ss, width, ' ');
            std::getline(ss, height);
            level.width = std::stoi(width);
            level.height = std::stoi(height);

            std::string tile;
            while(std::getline(ss,tile,',') )
            {
                 level.data.push_back(std::stoi(tile));
            }
            result.push_back(level);
        }
    } else {
        SH_ERROR("Cannot open level file.");
    }

    return result;
}

static const uint32_t TILE_SIZE = 16;

void Level::Load() {
    TextureAtlas atlas(MakeRef<Texture>("assets/textures/tilemap.png"),
                       {

                               {{ 0 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 1 Wall top left
                               {{ 1 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 2 Wall top center
                               {{ 2 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 3 Wall top right
                               {{ 0 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 4 Wall left
                               {{ 1 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 5 Wall center
                               {{ 2 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 6 Wall right
                               {{ 0 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 7 Floor left
                               {{ 1 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 8 Floor center
                               {{ 2 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 9 Floor right

                               {{ 0 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 10
                               {{ 1 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 11
                               {{ 2 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 12
                               {{ 3 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 13
                               {{ 0 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 14
                               {{ 1 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 15
                               {{ 2 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 16
                               {{ 3 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 17
                               {{ 0 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 18
                               {{ 1 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 19
                               {{ 2 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 20
                               {{ 3 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 21

                               {{ 5 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 22
                               {{ 6 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 23
                               {{ 5 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 24
                               {{ 6 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 25
                               {{ 5 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 26
                               {{ 6 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 27

                               {{ 8 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 28
                               {{ 7 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 29
                               {{ 8 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 30

                               {{ 10 * TILE_SIZE, 11 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 31
                               {{ 11 * TILE_SIZE, 11 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 32
                               {{ 10 * TILE_SIZE, 10 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 33
                               {{ 11 * TILE_SIZE, 10 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 34
                               {{ 10 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 35
                               {{ 11 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 36

                               {{ 2 * TILE_SIZE, 12 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 37

                               {{ 3 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 38
                               {{ 4 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 39

                               {{ 1 * TILE_SIZE, 12 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 40

                               {{ 5 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 41
                               {{ 6 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 42
                               {{ 5 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 43
                               {{ 6 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 44

                               {{ 8 * TILE_SIZE, 5 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 45
                       });


    mTiles.clear();
    for (auto& levelData : LoadLevelData("assets/levels/level1.level")) {
        for (int row = 0; row < levelData.height; row++) {
            for (int col = 0; col < levelData.width; col++) {
                int index = levelData.data[row * levelData.width + col] - 1;

                if (index < 0)
                    continue;

                mTiles.emplace_back(atlas[index], glm::vec3{ col, levelData.width - row, 0.0f }, glm::vec2{ 1, 1 });
            }
        }
    }
}

void Level::Draw() {
    for (auto& tile : mTiles) {
        tile.Draw();
    }
}