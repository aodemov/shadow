#pragma once

#include <typeindex>
#include "shadow/ecs/entity.h"

namespace Shadow {
class Component {
public:
    using ComponentType = std::type_index;
    template<class T>
    static ComponentType GetComponentType() {
        return typeid(T);
    }
};
}