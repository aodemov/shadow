#pragma once

#include <typeindex>

namespace Shadow {
class Component {
public:
    using ComponentType = std::type_index;
    template<class T>
    static ComponentType GetComponentType() {
        return typeid(T);
    }

protected:
    friend class GameObject;
    GameObject* mObject = nullptr;
};
}