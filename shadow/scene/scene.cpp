#include "scene.h"

#include "shadow/ecs/game_object.h"

namespace Shadow {
void Scene::Add(Ref<GameObject> object) {
    object->mScene = this;
    mGameObjects.push_back(std::move(object));
}

void Scene::Destroy(Ref<GameObject> object) {
    object->mScene = nullptr;
    mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), object));
}

void Scene::Load() {
    for (auto& go : mGameObjects) {
        go->OnLoad();
    }
}

void Scene::OnEnable() {
    for (auto& go : mGameObjects) {
        go->OnEnable();
    }
}

void Scene::OnDisable() {
    for (auto& go : mGameObjects) {
        go->OnDisable();
    }
}

void Scene::Destroy() {
    for (auto& go : mGameObjects) {
        go->OnDestroy();
    }
}

void Scene::VariableUpdate(float delta) {
    for (auto& go : mGameObjects) {
        go->VariableUpdate(delta);
    }
}

void Scene::FixedUpdate(float delta) {
    for (auto& go : mGameObjects) {
        go->FixedUpdate(delta);
    }
}
}