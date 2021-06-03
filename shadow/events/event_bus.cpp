#include "event_bus.h"

namespace Shadow {
void EventBus::Emit(Event const& event) {
    auto handlerEntries = mListeners.equal_range(event.GetType());

    for (auto handlerEntry = handlerEntries.first; handlerEntry != handlerEntries.second; ++handlerEntry) {
        auto const& handler = handlerEntry->second;
        handler->Invoke(event);
    }
}
}