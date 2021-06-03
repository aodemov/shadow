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

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    template<class EventT>
    using Function = std::function<void(EventT const&)>;

    template<class T, class EventT>
    using MemberFunction = void(T::*)(EventT const&);

    template<class EventT>
    void AddListener(Function<EventT> function);

    template<class T, class EventT>
    void AddListener(T* instance, MemberFunction<T, EventT> memberFunction);


    template<class EventT>
    void RemoveListener(Function<EventT> function);

    template<class T, class EventT>
    void RemoveListener(T* instance, MemberFunction<T, EventT> memberFunction);

    void Emit(Event const& event);
    
private:
    std::multimap<EventType, std::shared_ptr<HandlerFunctionBase>> mListeners;
};

template<class EventT>
void EventBus::AddListener(Function<EventT> function) {
    mListeners.insert(std::make_pair<EventType, std::shared_ptr<HandlerFunction<EventT>>>(
            EventT::GetStaticType(),
            std::make_shared<HandlerFunction<EventT>>(function)
    ));
}

template<class T, class EventT>
void EventBus::AddListener(T* instance, MemberFunction<T, EventT> memberFunction) {
    AddListener<EventT>(std::bind(memberFunction, instance, std::placeholders::_1)); // TODO don't use bind
}

template<class EventT>
void EventBus::RemoveListener(Function<EventT> function) {
    auto handlerEntries = mListeners.equal_range(EventT::GetStaticType());

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = std::dynamic_pointer_cast<HandlerFunction<EventT>>(handlerEntry->second);
        if (handler.get()->mFunction == function) {
            mListeners.erase(handlerEntry);
            return;
        }
    }
}

template<class T, class EventT>
void EventBus::RemoveListener(T* instance, MemberFunction<T, EventT> memberFunction) {
    RemoveListener(std::bind(memberFunction, instance, std::placeholders::_1));
}

}
