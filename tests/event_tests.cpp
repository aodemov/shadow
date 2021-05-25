#include "gtest/gtest.h"

#include "runtime/events/event_bus.h"

#include <string>

using namespace Shadow;

static std::string flag;

class CustomEvent : public Event {
public:
    const char* GetName() const override { return "Custom Event"; }

    explicit CustomEvent(std::string const&& message)
            : message(message) {}

    std::string GetMessage() const {
        return message;
    }


private:
    std::string message;
};

class System {
public:
    System(EventBus& eventBus)
            : _eventBus(eventBus) {}

    ~System() = default;

    void Subscribe() {
        _eventBus.AddListener(&System::CustomEventHandler, this);
    }

    void Unsubscribe() {
        _eventBus.RemoveListener(&System::CustomEventHandler, this);
    }

    void CustomEventHandler(CustomEvent const& event) {
        flag = event.GetMessage();
    }

private:
    EventBus& _eventBus;
};

TEST(EventBus, EmitTest) {
    flag = "";

    EventBus bus;
    System sys(bus);
    sys.Subscribe();

    bus.Emit(CustomEvent("foo"));

    ASSERT_EQ(flag, "foo");
}

TEST(EventBus, RemoveListenerTest) {
    flag = "";

    EventBus bus;
    System sys(bus);
    sys.Subscribe();

    bus.Emit(CustomEvent("foo"));

    ASSERT_EQ(flag, "foo");

    flag = "";

    sys.Unsubscribe();

    bus.Emit(CustomEvent("bar"));

    ASSERT_EQ(flag, "");
}