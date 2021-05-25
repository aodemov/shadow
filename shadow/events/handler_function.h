#pragma once
#include "event.h"

namespace Shadow {
class EventBus;

class HandlerFunctionBase {
public:
    void Invoke(Event const& event) {
        _invoke(event);
    }

private:
    virtual void _invoke(Event const& event) = 0;
};

template<class EventType>
class HandlerFunction : public HandlerFunctionBase {
public:
    typedef std::function<void(EventType const&)> Function;

    explicit HandlerFunction(Function handlerFunction)
        : mFunction(handlerFunction) {}

    void _invoke(Event const& event) override {
        mFunction(*(static_cast<const EventType*>(&event)));
    }

private:
    Function mFunction;

    friend class EventBus;
};

}