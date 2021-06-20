#include "registry.h"

#include "shadow/components/tag_component.h"

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

uint32_t Registry::GetEntityWithTag(const std::string &tag) {
    for (auto& [e, c] : View<TagComponent>()) {
        if (c.Tag == tag)
            return e;
    }
}

}