#pragma once

#include "shadow/ecs/component.h"
#include "shadow/ecs/script.h"

namespace Shadow {
class ScriptComponent : public Component {
public:
    ScriptComponent() = default;
    ScriptComponent(const ScriptComponent&) = default;

    template<class T, typename... TArgs>
    void Bind(TArgs&&... args) {
        script = static_cast<Script*>(new T(std::forward<TArgs>(args)...));
        script->mObject = mObject;
    }

    Script* script = nullptr;
    bool loaded = false;
};
}
