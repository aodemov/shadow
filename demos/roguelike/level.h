#pragma once

#include "shadow/shadow.h"
#include "enemy.h"

using namespace Shadow;

struct LevelData {
    enum LayerType {
        Tilemap,
        Collider,
        Object,
    };

    uint8_t width;
    uint8_t height;
    float z;
    LayerType type;
    std::vector<int16_t> data;
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

            std::string width, height, type, z;
            std::getline(ss, width, ' ');
            std::getline(ss, height, ' ');
            std::getline(ss, type, ' ');
            std::getline(ss, z);
            level.width = std::stoi(width);
            level.height = std::stoi(height);
            level.z = std::stof(z);

            if (type == "tilemap")
                level.type = LevelData::LayerType::Tilemap;
            else if (type == "collider")
                level.type = LevelData::LayerType::Collider;
            else if (type == "object")
                level.type = LevelData::LayerType::Object;

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
        auto tilemap = MakeRef<Texture>("assets/textures/tilemap2.png");
        TextureAtlas atlas(tilemap,
                           {
                                   { 1,   { 1 * TILE_SIZE, 31 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 2,   { 2 * TILE_SIZE, 31 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 3,   { 3 * TILE_SIZE, 31 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 33,  { 1 * TILE_SIZE, 30 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 34,  { 2 * TILE_SIZE, 30 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 35,  { 3 * TILE_SIZE, 30 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 65,  { 1 * TILE_SIZE, 29 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 66,  { 2 * TILE_SIZE, 29 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 67,  { 3 * TILE_SIZE, 29 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 97,  { 1 * TILE_SIZE, 28 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 98,  { 2 * TILE_SIZE, 28 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 99,  { 3 * TILE_SIZE, 28 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 129, { 1 * TILE_SIZE, 27 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 130, { 2 * TILE_SIZE, 27 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 131, { 3 * TILE_SIZE, 27 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 161, { 1 * TILE_SIZE, 26 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 162, { 2 * TILE_SIZE, 26 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 163, { 3 * TILE_SIZE, 26 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 193, { 1 * TILE_SIZE, 25 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 194, { 2 * TILE_SIZE, 25 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 195, { 3 * TILE_SIZE, 25 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 224, { 0 * TILE_SIZE, 24 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 225, { 1 * TILE_SIZE, 24 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 226, { 2 * TILE_SIZE, 24 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 227, { 3 * TILE_SIZE, 24 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 256, { 0 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 257, { 1 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 258, { 2 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 259, { 3 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 260, { 4 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 261, { 5 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 262, { 6 * TILE_SIZE, 23 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 288, { 0 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 289, { 1 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 290, { 2 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 291, { 3 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 292, { 4 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 293, { 5 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 294, { 6 * TILE_SIZE, 22 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 322, { 2 * TILE_SIZE, 21 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 323, { 3 * TILE_SIZE, 21 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 417, { 1 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 418, { 2 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 419, { 3 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 420, { 4 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 421, { 5 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 422, { 6 * TILE_SIZE, 18 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 449, { 1 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 450, { 2 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 451, { 3 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 452, { 4 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 453, { 5 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 454, { 6 * TILE_SIZE, 17 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 481, { 1 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 482, { 2 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 483, { 3 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 484, { 4 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 485, { 5 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                                   { 486, { 6 * TILE_SIZE, 16 * TILE_SIZE }, { TILE_SIZE, TILE_SIZE }},
                           });

        for (auto& levelData : LoadLevelData("assets/levels/level2.level")) {
            if (levelData.type == LevelData::LayerType::Tilemap)
                for (int row = 0; row < levelData.height; row++) {
                    for (int col = 0; col < levelData.width; col++) {
                        int index = levelData.data[row * levelData.width + col];

                        if (index <= 0)
                            continue;

                        auto tile = CreateObject();
                        tile.AddComponent<Transform>(glm::vec2{ col, levelData.width - row }, 0.0f, glm::vec2{ 1, 1 });
                        Sprite s(atlas[index]);
                        tile.AddComponent<SpriteComponent>(Sprite(atlas[index])).sprite.mZ = levelData.z;
                    }
                }
            else if (levelData.type == LevelData::LayerType::Collider)
                for (int row = 0; row < levelData.height; row++) {
                    for (int col = 0; col < levelData.width; col++) {
                        bool value = levelData.data[row * levelData.width + col] == 1;

                        if (!value)
                            continue;

                        auto collider = CreateObject();
                        collider.AddComponent<Transform>(glm::vec2{ col, levelData.width - row }, 0.0f, glm::vec2{ 1, 1 });
                        collider.AddComponent<ColliderComponent>(glm::vec4{ 0, 0, 1, 1 });
                    }
                }
        }

        auto enemy = CreateObject();
        auto& script = enemy.AddComponent<ScriptComponent>().Bind<Enemy>();


//        // Animated torches
//        Animation torchAnimation(tilemap, 1.5f, {
//            { { 8  * 16, 5 * 16 }, { 16, 32 } },
//            { { 9  * 16, 5 * 16 }, { 16, 32 } },
//            { { 10 * 16, 5 * 16 }, { 16, 32 } },
//            { { 11 * 16, 5 * 16 }, { 16, 32 } },
//            { { 12 * 16, 5 * 16 }, { 16, 32 } },
//            { { 13 * 16, 5 * 16 }, { 16, 32 } },
//            { { 14 * 16, 5 * 16 }, { 16, 32 } },
//            { { 15 * 16, 5 * 16 }, { 16, 32 } },
//        });
//
//        AnimationController controller({
//            { "default", torchAnimation }
//        }, "default");
//
//        const std::vector<glm::vec2> torches {
//                { 8, 22 },
//                { 11, 22 },
//                { 8, 17 },
//                { 11, 17 },
//        };
//
//        for (auto tc : torches) {
//            auto& t = CreateObject();
//            t.AddComponent<Transform>(tc, 0.0f, glm::vec2{ 1, 2 });
//            t.AddComponent<SpriteComponent>().sprite.mZ = 0.5f;
//            t.AddComponent<AnimatorComponent>(controller);
//            t.AddComponent<ColliderComponent>(glm::vec4{ 0, 0, 1, 2 });
//        }
    }
    void VariableUpdate(float delta) override {

    }
};
