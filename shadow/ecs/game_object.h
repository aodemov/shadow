#pragma once

#include "shadow/scene/scene.h"

namespace Shadow {
class GameObject {
public:
    virtual void OnLoad() = 0;
    virtual void OnDestroy() = 0;

    virtual void FixedUpdate() = 0;
    virtual void VariableUpdate() = 0;

    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;

    glm::vec2 position { 0.0f, 0.0f };
    glm::vec2 scale { 1.0f, 1.0f };
    float rotation { 0.0f };
protected:
    template<class EventType>
    void On(EventBus::Function<EventType> function) {
        mScene->mEventBus.AddListener(function);
    }
private:
    Scene* mScene {nullptr};
};
}
