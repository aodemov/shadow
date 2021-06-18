#pragma once

#include "shadow/shadow.h"

using namespace Shadow;

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

class Level : public Script {
public:
    void OnLoad() override {
        auto tilemap = MakeRef<Texture>("assets/textures/tilemap.png");
        TextureAtlas atlas(tilemap,
                           {
                                   { 1, { 0 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 1 Wall top left
                                   { 2, { 1 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 2 Wall top center
                                   { 3, { 2 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 3 Wall top right
                                   { 4, { 0 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 4 Wall left
                                   { 5, { 1 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 5 Wall center
                                   { 6, { 2 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 6 Wall right
                                   { 7, { 0 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 7 Floor left
                                   { 8, { 1 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 8 Floor center
                                   { 9, { 2 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 9 Floor right

                                   { 10, { 0 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 10
                                   { 11, { 1 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 11
                                   { 12, { 2 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 12
                                   { 13, { 3 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 13
                                   { 14, { 0 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 14
                                   { 15, { 1 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 15
                                   { 16, { 2 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 16
                                   { 17, { 3 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 17
                                   { 18, { 0 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 18
                                   { 19, { 1 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 19
                                   { 20, { 2 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 20
                                   { 21, { 3 * TILE_SIZE, 7 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 21

                                   { 22, { 5 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 22
                                   { 23, { 6 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 23
                                   { 24, { 5 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 24
                                   { 25, { 6 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 25
                                   { 26, { 5 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 26
                                   { 27, { 6 * TILE_SIZE, 13 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 27

                                   { 28, { 8 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 28
                                   { 29, { 7 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 29
                                   { 30, { 8 * TILE_SIZE, 14 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 30

                                   { 31, { 10 * TILE_SIZE, 11 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 31
                                   { 32, { 11 * TILE_SIZE, 11 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 32
                                   { 33, { 10 * TILE_SIZE, 10 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 33
                                   { 34, { 11 * TILE_SIZE, 10 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 34
                                   { 35, { 10 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 35
                                   { 36, { 11 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 36

                                   { 37, { 2 * TILE_SIZE, 12 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 37

                                   { 38, { 3 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 38
                                   { 39, { 4 * TILE_SIZE, 15 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 39

                                   { 40, { 1 * TILE_SIZE, 12 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 40

                                   { 41, { 5 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 41
                                   { 42, { 6 * TILE_SIZE, 9 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 42
                                   { 43, { 5 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 43
                                   { 44, { 6 * TILE_SIZE, 8 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 44

                                   { 45, { 8 * TILE_SIZE, 5 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }}, // 45
                           });


        for (auto& levelData : LoadLevelData("assets/levels/level1.level")) {
            for (int row = 0; row < levelData.height; row++) {
                for (int col = 0; col < levelData.width; col++) {
                    int index = levelData.data[row * levelData.width + col];

                    if (index <= 0)
                        continue;

                    auto& tile = CreateObject();
                    tile.AddComponent<Transform>(glm::vec2{ col, levelData.width - row }, 0.0f, glm::vec2{ 1, 1 });
                    Sprite s(atlas[index]);
                    tile.AddComponent<SpriteComponent>(Sprite(atlas[index]));
                }
            }
        }

        // Animated torches
        Animation torchAnimation(tilemap, 1.5f, {
            { { 8  * 16, 5 * 16 }, { 16, 32 } },
            { { 9  * 16, 5 * 16 }, { 16, 32 } },
            { { 10 * 16, 5 * 16 }, { 16, 32 } },
            { { 11 * 16, 5 * 16 }, { 16, 32 } },
            { { 12 * 16, 5 * 16 }, { 16, 32 } },
            { { 13 * 16, 5 * 16 }, { 16, 32 } },
            { { 14 * 16, 5 * 16 }, { 16, 32 } },
            { { 15 * 16, 5 * 16 }, { 16, 32 } },
        });

        AnimationController controller({
            { "default", torchAnimation }
        }, "default");

        const std::vector<glm::vec2> torches {
                { 8, 22 },
                { 11, 22 },
                { 8, 17 },
                { 11, 17 },
        };

        for (auto tc : torches) {
            auto& t = CreateObject();
            t.AddComponent<Transform>(tc, 0.0f, glm::vec2{ 1, 2 });
            t.AddComponent<SpriteComponent>().sprite.mZ = 0.5f;
            t.AddComponent<AnimatorComponent>(controller);
            t.AddComponent<ColliderComponent>(glm::vec4{ 0, 0, 1, 2 });
        }
    }
    void VariableUpdate(float delta) override {

    }
};
