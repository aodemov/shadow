#pragma once

#include <map>

#include "shadow/scene/scene.h"

namespace Shadow {

class SceneManager {
public:
    static SceneManager& Instance() {
        static SceneManager instance;
        return instance;
    }

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    ~SceneManager() = default;

    Scene& GetCurrentScene() const { return *currentScene; }

    void Load(std::string const& name);

    void Add(std::string const& name, Scene* scene);
private:
    SceneManager();

    std::map<std::string, Scene*> scenes;
    Scene* currentScene;

    friend class GameLoop;
};

}
