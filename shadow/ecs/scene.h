#pragma once

#include "shadow/events/event.h"
#include "shadow/events/event_bus.h"


#include "shadow/ecs/component.h"
#include "shadow/ecs/entity.h"
#include "shadow/ecs/registry.h"

#include "shadow/renderer/camera.h"

namespace Shadow {
class Entity;

class Scene {
public:
    Scene();
    virtual ~Scene() = default;

    void Load();
    void OnEnable();
    void OnDisable();
    void Destroy();

    void FixedUpdate(float delta);
    void VariableUpdate(float delta);

    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mEventBus.AddListener(function);
    }

    Entity Create();
    void Destroy(Entity& object);

    void SetCamera(Camera* camera) { mSceneCamera = camera; }

private:
    friend class GameLoop;
    friend class Entity;

    Registry mRegistry;
    EventBus mEventBus;

    Camera* mSceneCamera = nullptr;
};

template<class T>
T& Entity::GetComponent() {
    return mScene->mRegistry.GetComponent<T>(mId);
};
template<class T, typename... TArgs>
T& Entity::AddComponent(TArgs&&... args) {
    return mScene->mRegistry.AddComponent<T>(mId, std::forward<TArgs>(args)...);
}
template<class T>
void Entity::RemoveComponent() {
    mScene->mRegistry.RemoveComponent<T>(mId);
}
template<class T>
bool Entity::HasComponent() {
    return mScene->mRegistry.HasComponent<T>(mId);
}

template<class EventType>
void Entity::On(EventBus::Function<EventType> function) {
    mScene->mEventBus.AddListener(function);
}

}
