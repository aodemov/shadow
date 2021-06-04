#pragma once

#include "shadow/events/event.h"
#include "shadow/events/event_bus.h"

namespace Shadow {
class GameObject;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Load();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void Destroy();

    virtual void FixedUpdate(float delta);
    virtual void VariableUpdate(float delta);

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
