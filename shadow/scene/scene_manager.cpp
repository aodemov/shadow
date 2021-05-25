#include "scene_manager.h"

namespace Shadow {

SceneManager::SceneManager()
    : mScenes(),
      mCurrentScene()
{}

void SceneManager::Add(const std::string &name, Scene *scene) {
    mScenes[name] = scene;
}

void SceneManager::Load(const std::string &name) {
    Scene* previousScene = mCurrentScene;
    mCurrentScene = mScenes.at(name);
    if (previousScene != nullptr) {
        previousScene->Destroy();
    }
    mCurrentScene->Create();
}

}
