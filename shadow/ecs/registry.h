#pragma once


namespace Shadow {
class GameObject;
class Scene;

class Registry {
public:
    Registry(Scene* scene)
        : mScene(scene) {}

    void AddObject(Ref<GameObject> object);
    void RemoveObject(const Ref<GameObject>& object);

    std::vector<Ref<GameObject>> GetObjects() { return mObjects; }
private:
    Scene* mScene;

    std::vector<Ref<GameObject>> mObjects {};
};
}
