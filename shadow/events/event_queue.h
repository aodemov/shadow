#pragma once

#include "shadow/events/event.h"

#include <typeindex>


namespace Shadow {
class EventQueue {
public:
    EventQueue() = default;
    ~EventQueue() = default;

    EventQueue(const EventQueue&) = delete;
    EventQueue& operator=(const EventQueue&) = delete;

    template<typename EventType>
    void Push(EventType const& event);
    void Pop();
    bool HasPending();
    const Event& Front();


private:
    std::queue<std::unique_ptr<Event>> mEventQueue;
};

template<typename EventType>
void EventQueue::Push(const EventType &event) {
    mEventQueue.push(std::unique_ptr<Event>(new EventType(event)));
}

}
