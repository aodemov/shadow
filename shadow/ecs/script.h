#pragma once

#include "shadow/ecs/game_object.h"

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
        mObject->On<EventType>(function);
    }

    template<class T>
    T& GetComponent() const {
        return mObject->GetComponent<T>();
    }
    template<class T, typename... TArgs>
    void AddComponent(TArgs&&... args) {
        mObject->AddComponent<T>(std::forward<TArgs>(args)...);
    }
    template<class T>
    void RemoveComponent() {
        mObject->RemoveComponent<T>();
    }
    template<class T>
    bool HasComponent() {
        return mObject->HasComponent<T>();
    }

private:
    friend class ScriptComponent;
    GameObject* mObject = nullptr;
};
}
