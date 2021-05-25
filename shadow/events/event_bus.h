#pragma once

#include <typeindex>
#include <map>
#include <queue>
#include <memory>

#include "handler_function.h"

namespace Shadow {

class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    template<class EventType>
    using Function = std::function<void(EventType const&)>;

    template<class T, class EventType>
    using MemberFunction = void(T::*)(EventType const&);

    void ProcessOne();
    void ProcessAll();
    bool HasPending();


    template<class EventType>
    void AddListener(Function<EventType> function);

    template<class T, class EventType>
    void AddListener(T* instance, MemberFunction<T, EventType> memberFunction);


    template<class EventType>
    void RemoveListener(Function<EventType> function);

    template<class T, class EventType>
    void RemoveListener(T* instance, MemberFunction<T, EventType> memberFunction);


    template<typename EventType>
    void EmitImmediately(EventType const& event);

    template<typename EventType>
    void Push(EventType const& event);

private:
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void Emit(std::type_index eventId, Event const& event);

    std::multimap<std::type_index, std::shared_ptr<HandlerFunctionBase>> mListeners;
    std::queue<std::pair<std::type_index, std::unique_ptr<Event>>> mEventQueue;

    std::mutex mMutex;
};

template<class EventType>
void EventBus::AddListener(Function<EventType> function) {
    std::lock_guard<std::mutex> lock(mMutex);

    mListeners.insert(std::make_pair<std::type_index, std::shared_ptr<HandlerFunction<EventType>>>(
            typeid(EventType),
            std::make_shared<HandlerFunction<EventType>>(function)
    ));
}

template<class T, class EventType>
void EventBus::AddListener(T* instance, MemberFunction<T, EventType> memberFunction) {
    AddListener<EventType>(std::bind(memberFunction, instance, std::placeholders::_1));
}

template<class EventType>
void EventBus::RemoveListener(Function<EventType> function) {
    std::lock_guard<std::mutex> lock(mMutex);

    auto handlerEntries = mListeners.equal_range(typeid(EventType));

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = std::dynamic_pointer_cast<HandlerFunction<EventType>>(handlerEntry->second);
        if (handler.get()->mFunction == function) {
            mListeners.erase(handlerEntry);
            return;
        }
    }
}

template<class T, class EventType>
void EventBus::RemoveListener(T* instance, MemberFunction<T, EventType> memberFunction) {
    RemoveListener(std::bind(memberFunction, instance, std::placeholders::_1));
}

template<typename EventType>
void EventBus::EmitImmediately(EventType const& event) {
    Emit(typeid(EventType), event);
}

template<typename EventType>
void EventBus::Push(const EventType &event) {
    std::lock_guard<std::mutex> lock(mMutex);

    if (mListeners.count(typeid(EventType)) > 0) {
        mEventQueue.push(std::make_pair<std::type_index, std::unique_ptr<Event>>(typeid(EventType), std::unique_ptr<Event>(new EventType(event))));
    }
}

}
