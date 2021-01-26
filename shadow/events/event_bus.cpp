#include "event_bus.h"

namespace Shadow {
void EventBus::emit(std::type_index eventId, Event const& event) {
    auto handlerEntries = listeners.equal_range(eventId);

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = handlerEntry->second;
        handler->invoke(event);
    }
}

bool EventBus::hasPending() {
    std::lock_guard<std::mutex> lock(mutex);

    return !eventQueue.empty();
}

void EventBus::processOne() {
    std::lock_guard<std::mutex> lock(mutex);

    if(!eventQueue.empty()) {
        const auto& [eventId, event_pt] = eventQueue.front();
        emit(eventId, *event_pt.get());
        eventQueue.pop();
    }
}

void EventBus::processAll() {
    std::lock_guard<std::mutex> lock(mutex);

    while(!eventQueue.empty()) {
        const auto& [eventId, event_pt] = eventQueue.front();

        emit(eventId, *event_pt.get());
        eventQueue.pop();
    }
}
}