#include "registry.h"

uint32_t generateEntityId() {
    static uint32_t sId = 0;
    return sId++;
}

namespace Shadow {
uint32_t Registry::CreateEntity() {

    uint32_t e = generateEntityId();
    return e;
}

void Registry::RemoveEntity(uint32_t entity) {

}

}