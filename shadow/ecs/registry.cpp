#include "registry.h"

#include "game_object.h"

namespace Shadow {
void Registry::AddObject(Ref<GameObject> object) {
    object->mScene = mScene;

    mObjects.emplace_back(std::move(object));
}

void Registry::RemoveObject(const Ref<GameObject>& object) {
    mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), object));
}
}