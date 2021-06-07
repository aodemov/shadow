#pragma once


namespace Shadow {
class GameObject;
class Scene;

class Registry {
public:
    Registry(Scene* scene)
        : mScene(scene) {}

    GameObject& CreateObject();
    void RemoveObject(GameObject& object);

    std::vector<Ref<GameObject>> GetObjects() { return mObjects; }
private:
    Scene* mScene;

    std::vector<Ref<GameObject>> mObjects {};
};
}
