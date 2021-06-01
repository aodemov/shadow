#pragma once

namespace Shadow {

using EventType = uint16_t;

class Event {
public:
    virtual EventType GetType() const = 0;
    virtual std::string ToString() const { return std::to_string(GetType()); }

    enum : EventType {
        WindowClose = 0,
        WindowResize,
        KeyPressed,
        KeyReleased,
        KeyRepeated,
        MouseMoved,
        MousePressed,
        MouseReleased,
        MouseScrolled,
    };
};

}
