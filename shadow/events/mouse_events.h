#pragma once

#include "event.h"
#include "shadow/core/input/key_codes.h"

namespace Shadow {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const double x, const double y)
            : x(x), y(y) {}

    double GetX() const { return x; }
    double GetY() const { return y; }

    const char* GetName() const override { return "MouseMovedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << x << "; " << y;
        return ss.str();
    }

private:
    double x, y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const double xOffset, const double yOffset)
            : x(xOffset), y(yOffset) {}

    double GetXOffset() const { return x; }
    double GetYOffset() const { return y; }

    const char* GetName() const override { return "MouseScrolledEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << x << "; " << y;
        return ss.str();
    }

private:
    double x, y;
};

class MousePressedEvent : public Event {
public:
    MousePressedEvent(const MouseCode mouseCode, const KeyModifiers = Modifiers::None)
            : mouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mouseCode; }
    KeyModifiers GetModifiers() const { return mods; }

    const char* GetName() const override { return "MousePressedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MousePressedEvent: " << mouseCode;
        return ss.str();
    }

private:
    MouseCode mouseCode;
    KeyModifiers mods;
};

class MouseReleasedEvent : public Event {
public:
    MouseReleasedEvent(const MouseCode mouseCode, const KeyModifiers = Modifiers::None)
            : mouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mouseCode; }
    KeyModifiers GetModifiers() const { return mods; }

    const char* GetName() const override { return "MouseReleasedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseReleasedEvent: " << mouseCode;
        return ss.str();
    }

private:
    MouseCode mouseCode;
    KeyModifiers mods;
};


}
