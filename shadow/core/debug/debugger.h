#pragma once

#include "shadow/core/debug/statistics.h"
#include "shadow/events/event_bus.h"

namespace Shadow {
struct Properties {
    bool ShowColliders = false;
    bool ShowTriggers = false;
};

class Debugger {
public:
    Debugger();
    ~Debugger();

    void Init();
    void Shutdown();

    void Update(float delta);

    void Show();
    void Hide();

    static inline Statistics Stats;
    static inline Properties Props;

private:
    bool mVisible = false;
    EventBus mEventBus;
    friend class GameLoop;
};
}
