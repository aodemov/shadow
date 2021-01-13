#pragma once
#include "event.h"

namespace Shadow {

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
    typedef void (T::*MemberFunction)(EventType const&);

    HandlerFunction(MemberFunction memberFunction, T* instance)
        :   _memberFunction(memberFunction),
            _instance(instance) { }

    void _invoke(Event const& event) override {
        (_instance->*_memberFunction)(*(static_cast<const EventType*>(&event)));
    }

private:
    T* _instance;
    MemberFunction _memberFunction;
};

}