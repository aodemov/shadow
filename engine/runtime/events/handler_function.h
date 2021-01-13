#pragma once
#include "event.h"

namespace Shadow {
class EventBus;

class HandlerFunctionBase {
public:
    void invoke(Event const& event) {
        _invoke(event);
    }

private:
    virtual void _invoke(Event const& event) = 0;
};

template<class T, class EventType>
class HandlerFunction : public HandlerFunctionBase {
public:
    friend class EventBus;
    typedef void (T::*MemberFunction)(EventType const&);

    HandlerFunction(MemberFunction memberFunction, T* instance)
        :   memberFunction(memberFunction),
            instance(instance) { }

    void _invoke(Event const& event) override {
        (instance->*memberFunction)(*(static_cast<const EventType*>(&event)));
    }

private:
    T* instance;
    MemberFunction memberFunction;
};

}