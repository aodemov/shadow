#include "event_queue.h"

namespace Shadow {
void EventQueue::Pop() {
    mEventQueue.pop();
}

const Event& EventQueue::Front() {
    return *mEventQueue.front().get();
}

bool EventQueue::HasPending() {
    return !mEventQueue.empty();
}
}