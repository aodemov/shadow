#include "scene.h"

namespace Shadow {
void Scene::Add(Ref<GameObject> object) {
    mGameObjects.push_back(std::move(object));
}

void Scene::Destroy(Ref<GameObject> object) {
    mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), object));
}
}