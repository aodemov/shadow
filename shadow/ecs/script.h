#pragma once

#include "shadow/ecs/entity.h"

namespace Shadow {
class Script {
public:
    Script() = default;
    Script(const Script&) = default;

    virtual void OnLoad() {}
    virtual void OnDestroy() {}

    virtual void FixedUpdate(float delta) {}
    virtual void VariableUpdate(float delta) {}

    virtual void OnEnable() {}
    virtual void OnDisable() {}

protected:
    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mEntity.On<EventType>(function);
    }

    Entity CreateObject() {
        return mEntity.mScene->Create();
    }

    void DestroyObject(Entity& object) {
        mEntity.mScene->Destroy(object);
    }

    Scene& GetScene() {
        return *mEntity.mScene;
    }

    template<class T>
    T& GetComponent() {
        return mEntity.GetComponent<T>();
    }
    template<class T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        return mEntity.AddComponent<T>(std::forward<TArgs>(args)...);
    }
    template<class T>
    void RemoveComponent() {
        mEntity.RemoveComponent<T>();
    }
    template<class T>
    bool HasComponent() {
        return mEntity.HasComponent<T>();
    }

    Entity GetEntityWithTag(const std::string& tag) {
        return mEntity.GetEntityWithTag(tag);
    }

private:
    friend class Scene;
    Entity mEntity;
};
}
