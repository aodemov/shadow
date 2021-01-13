#pragma once

#include <list>
#include <map>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <functional>

#include "handler_function.h"

namespace Shadow {

class EventBus {
public:
    EventBus();
    ~EventBus();

    template<class T, class EventType>
    void addListener(void (T::*memberFunction)(EventType const&), T* instance) {
        listeners.insert(std::make_pair<std::type_index, std::shared_ptr<HandlerFunction<T, EventType>>>(
                typeid(EventType),
                std::make_shared<HandlerFunction<T, EventType>>
                    (memberFunction, instance)
            ));
    }

    template<typename EventType>
    void emit(EventType const& event) {
        auto handlerEntries = listeners.equal_range(typeid(EventType));

        for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
            auto const& handler = handlerEntry->second;
            handler->invoke(event);
        }
    }

private:
    std::multimap<std::type_index, std::shared_ptr<HandlerFunctionBase>> listeners;
};

}
