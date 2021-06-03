#pragma once

#include "shadow/events/event.h"
#include "shadow/events/event_bus.h"

namespace Shadow {

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Load() = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Destroy() = 0;

    virtual void FixedUpdate(float delta) = 0;
    virtual void VariableUpdate(float delta) = 0;

//    virtual void OnEvent(const Event& event) = 0;
protected:
    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mEventBus.AddListener(function);
    }
private:
    friend class GameLoop;

    EventBus mEventBus;
};

}
