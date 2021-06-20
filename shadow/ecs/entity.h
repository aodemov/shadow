#pragma once

#include "shadow/events/event_bus.h"

namespace Shadow {
class Entity {
public:
    Entity() = default;
    ~Entity() = default;

    Entity(uint32_t id, class Scene* scene)
        : mId(id),
          mScene(scene) {}

    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default;

    template<class T>
    T& GetComponent();
    template<class T, typename... TArgs>
    T& AddComponent(TArgs&&... args);
    template<class T>
    void RemoveComponent();
    template<class T>
    bool HasComponent();

    Entity GetEntityWithTag(const std::string& tag);

    bool operator==(Entity& other) const {
        return mId == other.mId;
    }
protected:

private:
    friend class Registry;
    friend class Script;
    friend class Scene;
    friend class ScriptComponent;

    template<class EventType>
    void On(EventBus::Function<EventType> function);

    class Scene* mScene {nullptr};
    uint32_t mId = -1;
};

}
