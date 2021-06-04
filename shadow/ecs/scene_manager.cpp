#include "scene_manager.h"

namespace Shadow {

SceneManager::SceneManager()
    : mScenes(),
      mCurrentScene()
{}

void SceneManager::Init() {

}

void SceneManager::Shutdown() {
    for (auto & scene : mScenes) {
        Destroy(scene.first);
        delete scene.second.first;
    }

    mScenes.clear();
}


void SceneManager::Add(const std::string &name, Scene *scene) {
    mScenes[name] = {scene, SceneState::NotLoaded};
}

void SceneManager::Remove(const std::string &name) {
    auto& scene = mScenes.at(name);
    if (scene.second == SceneState::Loaded)
        Destroy(name);

    delete scene.first;
    mScenes.erase(name);
}

void SceneManager::Load(const std::string &name) {
    auto& scene = mScenes.at(name);

    if (scene.second == SceneState::Loaded)
        return;

    scene.first->Load();
    scene.second = SceneState::Loaded;
}

void SceneManager::Destroy(const std::string &name) {
    auto& scene = mScenes.at(name);

    if (scene.first == mCurrentScene)
        Hide(name);

    scene.first->Destroy();
    scene.second = SceneState::NotLoaded;
}

void SceneManager::Show(const std::string &name) {
    auto& scene = mScenes.at(name);

    if (scene.first == mCurrentScene)
        return;

    if (scene.second == SceneState::NotLoaded)
        Load(name);


    if (mCurrentScene != nullptr)
        mCurrentScene->OnDisable();

    mCurrentScene = mScenes.at(name).first;
    mCurrentSceneName = name;
    mCurrentScene->OnEnable();
}

void SceneManager::Hide(const std::string &name) {
    auto& scene = mScenes.at(name);

    if (scene.first != mCurrentScene)
        return;

    mCurrentScene->OnDisable();
    mCurrentScene = nullptr;
    mCurrentSceneName = "";
}

}
