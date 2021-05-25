#include "event_bus.h"

namespace Shadow {
void EventBus::Emit(std::type_index eventId, Event const& event) {
    auto handlerEntries = mListeners.equal_range(eventId);

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = handlerEntry->second;
        handler->Invoke(event);
    }
}

bool EventBus::HasPending() {
    std::lock_guard<std::mutex> lock(mMutex);

    return !mEventQueue.empty();
}

void EventBus::ProcessOne() {
    std::lock_guard<std::mutex> lock(mMutex);

    if(!mEventQueue.empty()) {
        const auto& [eventId, event_pt] = mEventQueue.front();
        Emit(eventId, *event_pt.get());
        mEventQueue.pop();
    }
}

void EventBus::ProcessAll() {
    std::lock_guard<std::mutex> lock(mMutex);

    while(!mEventQueue.empty()) {
        const auto& [eventId, event_pt] = mEventQueue.front();

        Emit(eventId, *event_pt.get());
        mEventQueue.pop();
    }
}
}