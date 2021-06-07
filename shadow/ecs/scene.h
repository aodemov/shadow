#pragma once

#include "shadow/events/event.h"
#include "shadow/events/event_bus.h"

#include "shadow/ecs/registry.h"

#include "shadow/renderer/camera.h"

namespace Shadow {
class GameObject;

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

    GameObject& Create();
    void Destroy(GameObject& object);

    void SetCamera(Camera* camera) { mSceneCamera = camera; }

private:
    friend class GameLoop;
    friend class GameObject;

    Registry mRegistry;
    EventBus mEventBus;

    Camera* mSceneCamera = nullptr;
};

}
