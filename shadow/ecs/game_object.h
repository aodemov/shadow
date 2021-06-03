#pragma once

#include "shadow/scene/scene.h"

namespace Shadow {
class GameObject {
public:
    GameObject() = default;
    ~GameObject() = default;

    GameObject(const GameObject&) = default;
    GameObject& operator=(const GameObject&) = default;

    virtual void OnLoad() {};
    virtual void OnDestroy() {};

    virtual void FixedUpdate(float delta) {};
    virtual void VariableUpdate(float delta) {};

    virtual void OnEnable() {};
    virtual void OnDisable() {};

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
