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
        _eventBus.addListener(&System::CustomEventHandler, this);
    }

    void Unsubscribe() {
        _eventBus.removeListener(&System::CustomEventHandler, this);
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

    bus.emit(CustomEvent("foo"));

    ASSERT_EQ(flag, "foo");
}

TEST(EventBus, RemoveListenerTest) {
    flag = "";

    EventBus bus;
    System sys(bus);
    sys.Subscribe();

    bus.emit(CustomEvent("foo"));

    ASSERT_EQ(flag, "foo");

    flag = "";

    sys.Unsubscribe();

    bus.emit(CustomEvent("bar"));

    ASSERT_EQ(flag, "");
}