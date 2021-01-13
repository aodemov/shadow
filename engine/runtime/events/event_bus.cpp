#include "event_bus.h"

#include <iostream>

namespace Shadow {

EventBus::EventBus() = default;
EventBus::~EventBus() = default;

//    template<class T, class EventType>
//    void removeListener(void (T::*memberFunction)(EventType*), T* instance) {
//        auto it = std::find_if(listeners.begin(), listeners.end(), [&](std::pair<std::type_index const&, std::shared_ptr<HandlerFunctionBase>> const&) {
//
//        });
//    }

}