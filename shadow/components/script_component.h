#pragma once

#include "shadow/ecs/component.h"
#include "shadow/ecs/script.h"

namespace Shadow {
class ScriptComponent : public Component {
public:
    ScriptComponent() = default;
    ScriptComponent(const ScriptComponent&) = delete;
    ScriptComponent(ScriptComponent&& other) noexcept {
        script = other.script;
        other.script = nullptr;
        loaded = other.loaded;
    }
    ~ScriptComponent()  {
        delete script;
    };

    template<class T, typename... TArgs>
    T& Bind(TArgs&&... args) {
        T* instance = new T(std::forward<TArgs>(args)...);
        script = static_cast<Script*>(instance);
        return *instance;
    }

    Script* script = nullptr;
    bool loaded = false;
};
}
