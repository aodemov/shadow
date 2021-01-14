#pragma once

#include <typeindex>
#include <map>

#include "handler_function.h"

namespace Shadow {

class EventBus {
public:
    static EventBus& Instance() {
        static EventBus instance;

        return instance;
    }

    template<class T, class EventType>
    void addListener(void (T::*memberFunction)(EventType const&), T* instance);

    template<class T, class EventType>
    void removeListener(void (T::*memberFunction)(EventType const&), T* instance);

    template<typename EventType>
    void emit(EventType const& event);

private:
    EventBus() = default;
    ~EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    std::multimap<std::type_index, std::shared_ptr<HandlerFunctionBase>> listeners;

    std::mutex mutex;
};


template<class T, class EventType>
void EventBus::addListener(void (T::*memberFunction)(EventType const&), T* instance) {
    std::lock_guard<std::mutex> lock(mutex);

    listeners.insert(std::make_pair<std::type_index, std::shared_ptr<HandlerFunction<T, EventType>>>(
            typeid(EventType),
            std::make_shared<HandlerFunction<T, EventType>>
                    (memberFunction, instance)
    ));
}

template<class T, class EventType>
void EventBus::removeListener(void (T::*memberFunction)(EventType const&), T* instance) {
    std::lock_guard<std::mutex> lock(mutex);

    auto handlerEntries = listeners.equal_range(typeid(EventType));

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = std::dynamic_pointer_cast<HandlerFunction<T, EventType>>(handlerEntry->second);
        if (handler.get()->instance == instance && handler.get()->memberFunction == memberFunction) {
            listeners.erase(handlerEntry);
            return;
        }
    }
}

template<typename EventType>
void EventBus::emit(EventType const& event) {
    std::lock_guard<std::mutex> lock(mutex);

    auto handlerEntries = listeners.equal_range(typeid(EventType));

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = handlerEntry->second;
        handler->invoke(event);
    }
}

}
