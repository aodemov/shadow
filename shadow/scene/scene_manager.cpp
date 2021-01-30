#include "scene_manager.h"

namespace Shadow {

SceneManager::SceneManager()
    : scenes(),
      currentScene()
{}

void SceneManager::Add(const std::string &name, Scene *scene) {
    scenes[name] = scene;
}

void SceneManager::Load(const std::string &name) {
    Scene* previousScene = currentScene;
    currentScene = scenes.at(name);
    if (previousScene != nullptr) {
        previousScene->Destroy();
    }
    currentScene->Create();
}

}
