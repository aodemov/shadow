#pragma once

#include "shadow/ecs/scene.h"
#include "shadow/ecs/component.h"

namespace Shadow {
class GameObject {
public:
    GameObject() = default;
    ~GameObject() = default;

    GameObject(const GameObject&) = default;
    GameObject& operator=(const GameObject&) = default;

    virtual void OnLoad() {}
    virtual void OnDestroy() {}

    virtual void FixedUpdate(float delta) {}
    virtual void VariableUpdate(float delta) {}

    virtual void OnEnable() {}
    virtual void OnDisable() {}

    template<class T>
    T& GetComponent() const;
    template<class T, typename... TArgs>
    void AddComponent(TArgs&&... args);
    template<class T>
    void RemoveComponent();
    template<class T>
    bool HasComponent();
protected:
    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mScene->mEventBus.AddListener(function);
    }
private:
    friend class Registry;

    class Scene* mScene {nullptr};
    std::map<Component::ComponentType, Scope<Component>> mComponents {};
};

template<class T>
T& GameObject::GetComponent() const {
    return *(static_cast<T*>(mComponents.at(Component::GetComponentType<T>()).get()));
}

template<class T, typename... TArgs>
void GameObject::AddComponent(TArgs&&... args) {
    Scope<T> component = MakeScope<T>(std::forward<TArgs>(args)...);

    mComponents.emplace(Component::GetComponentType<T>(), std::move(component));
}

template<class T>
void GameObject::RemoveComponent() {
    mComponents.erase(Component::GetComponentType<T>());
}

template<class T>
bool GameObject::HasComponent() {
    return mComponents.contains(Component::GetComponentType<T>());
}

}
