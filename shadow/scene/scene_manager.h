#pragma once

#include <map>

#include "shadow/scene/scene.h"

namespace Shadow {

enum class SceneState {
    NotLoaded = 0,
    Loaded,
};

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;


    void Add(std::string const& name, Scene* scene);
    void Remove(std::string const& name);

    void Load(std::string const& name);
    void Destroy(std::string const& name);

    void Show(std::string const& name);
    void Hide(std::string const& name);

    inline std::string GetCurrentScene() const { return mCurrentSceneName; }

private:
    std::map<std::string, std::pair<Scene*, SceneState>> mScenes;
    Scene* mCurrentScene;
    std::string mCurrentSceneName;

    inline Scene* CurrentScene() const { return mCurrentScene; }

    friend class GameLoop;
};

}
