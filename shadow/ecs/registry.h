#pragma once

#include "shadow/ecs/component.h"
#include "shadow/ecs/pool.h"
#include "shadow/ecs/entity.h"

namespace Shadow {
class Scene;

class Registry {
public:
    explicit Registry() = default;
    uint32_t CreateEntity();
    void RemoveEntity(uint32_t entity);

    template<class T>
    T& GetComponent(uint32_t entity);
    template<class T, typename... TArgs>
    T& AddComponent(uint32_t entity, TArgs&&... args);
    template<class T>
    void RemoveComponent(uint32_t entity);
    template<class T>
    bool HasComponent(uint32_t entity);

    uint32_t GetEntityWithTag(const std::string& tag);

    template<class T>
    Pool<T>& View();

private:
    std::map<Component::ComponentType, void*> mPools{};
};

template<class T>
T& Registry::GetComponent(uint32_t entity) {
    auto type = Component::GetComponentType<T>();

    return static_cast<Pool<T>*>(mPools[type])->getComponent(entity);
}

template<class T, typename... TArgs>
T& Registry::AddComponent(uint32_t entity, TArgs&&... args) {
    auto type = Component::GetComponentType<T>();

    if (!mPools.contains(type)) {
        mPools.emplace(type, static_cast<void*>(new Pool<T>()));
    }

    T c(std::forward<TArgs>(args)...);
    static_cast<Pool<T>*>(mPools[type])->add(entity, c);

    return GetComponent<T>(entity); // TODO fix
}

template<class T>
void Registry::RemoveComponent(uint32_t entity) {
    auto type = Component::GetComponentType<T>();

    std::static_pointer_cast<Pool<T>, void>(mPools[type])->remove(entity);
}

template<class T>
bool Registry::HasComponent(uint32_t entity) {
    auto type = Component::GetComponentType<T>();

    return static_cast<Pool<T>*>(mPools[type])->has(entity);
}

template<class T>
Pool<T>& Registry::View() {
    auto type = Component::GetComponentType<T>();
    
    if (!mPools.contains(type)) {
        mPools.emplace(type, static_cast<void*>(new Pool<T>()));
    }

    return *static_cast<Pool<T>*>((mPools[type]));
}
}
