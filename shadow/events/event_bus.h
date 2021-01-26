#pragma once

#include <typeindex>
#include <map>
#include <queue>
#include <memory>

#include "handler_function.h"

namespace Shadow {

class EventBus {
public:
    template<class EventType>
    using Function = std::function<void(EventType const&)>;

    template<class T, class EventType>
    using MemberFunction = void(T::*)(EventType const&);


    static EventBus& Instance() {
        static EventBus instance;

        return instance;
    }

    void processOne();
    void processAll();
    bool hasPending();


    template<class EventType>
    void addListener(Function<EventType> function);

    template<class T, class EventType>
    void addListener(T* instance, MemberFunction<T, EventType> memberFunction);


    template<class EventType>
    void removeListener(Function<EventType> function);

    template<class T, class EventType>
    void removeListener(T* instance, MemberFunction<T, EventType> memberFunction);


    template<typename EventType>
    void emitImmediately(EventType const& event);

    template<typename EventType>
    void push(EventType const& event);

private:
    EventBus() = default;
    ~EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void emit(std::type_index eventId, Event const& event);

    std::multimap<std::type_index, std::shared_ptr<HandlerFunctionBase>> listeners;
    std::queue<std::pair<std::type_index, std::unique_ptr<Event>>> eventQueue;

    std::mutex mutex;
};

template<class EventType>
void EventBus::addListener(Function<EventType> function) {
    std::lock_guard<std::mutex> lock(mutex);

    listeners.insert(std::make_pair<std::type_index, std::shared_ptr<HandlerFunction<EventType>>>(
            typeid(EventType),
            std::make_shared<HandlerFunction<EventType>>(function)
    ));
}

template<class T, class EventType>
void EventBus::addListener(T* instance, MemberFunction<T, EventType> memberFunction) {
    addListener<EventType>(std::bind(memberFunction, instance, std::placeholders::_1));
}

template<class EventType>
void EventBus::removeListener(Function<EventType> function) {
    std::lock_guard<std::mutex> lock(mutex);

    auto handlerEntries = listeners.equal_range(typeid(EventType));

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = std::dynamic_pointer_cast<HandlerFunction<EventType>>(handlerEntry->second);
        if (handler.get()->function == function) {
            listeners.erase(handlerEntry);
            return;
        }
    }
}

template<class T, class EventType>
void EventBus::removeListener(T* instance, MemberFunction<T, EventType> memberFunction) {
    removeListener(std::bind(memberFunction, instance, std::placeholders::_1));
}

template<typename EventType>
void EventBus::emitImmediately(EventType const& event) {
    emit(typeid(EventType), event);
}

template<typename EventType>
void EventBus::push(const EventType &event) {
    std::lock_guard<std::mutex> lock(mutex);

    if (listeners.count(typeid(EventType)) > 0) {
        eventQueue.push(std::make_pair<std::type_index, std::unique_ptr<Event>>(typeid(EventType), std::unique_ptr<Event>(new EventType(event))));
    }
}

}
