#include "registry.h"

#include "game_object.h"

namespace Shadow {
GameObject& Registry::CreateObject() {
    auto object = MakeRef<GameObject>(); // TODO ref -> scope
    object->mScene = mScene;

    mObjects.emplace_back(object);
    return *object;
}

void Registry::RemoveObject(GameObject& object) {
    mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), Ref<GameObject>(&object)));
}
}