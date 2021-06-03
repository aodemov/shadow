#pragma once

#include "shadow/events/event.h"
#include "shadow/events/event_bus.h"

namespace Shadow {
class GameObject;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Load() = 0;
    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;
    virtual void Destroy() = 0;

    virtual void FixedUpdate(float delta) = 0;
    virtual void VariableUpdate(float delta) = 0;

protected:
    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mEventBus.AddListener(function);
    }

    void Add(Ref<GameObject> object);
    void Destroy(Ref<GameObject> object);
private:
    std::vector<Ref<GameObject>> mGameObjects;

    friend class GameLoop;
    friend class GameObject;

    EventBus mEventBus;
};

}
