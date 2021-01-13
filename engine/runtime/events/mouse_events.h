#pragma once

#include "runtime/events/event.h"
#include "core/input/key_codes.h"

namespace Shadow {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y)
            : x(x), y(y) {}

    float GetX() const { return x; }
    float GetY() const { return y; }

    const char* GetName() const override { return "MouseMovedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << x << "; " << y;
        return ss.str();
    }

private:
    float x, y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
            : x(xOffset), y(yOffset) {}

    float GetXOffset() const { return x; }
    float GetYOffset() const { return y; }

    const char* GetName() const override { return "MouseScrolledEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << x << "; " << y;
        return ss.str();
    }

private:
    float x, y;
};

class MousePressedEvent : public Event {
public:
    MousePressedEvent(const MouseCode mouseCode)
            : mouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mouseCode; }

    const char* GetName() const override { return "MousePressedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MousePressedEvent: " << mouseCode;
        return ss.str();
    }

private:
    MouseCode mouseCode;
};

class MouseReleasedEvent : public Event {
public:
    MouseReleasedEvent(const MouseCode mouseCode)
            : mouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mouseCode; }

    const char* GetName() const override { return "MouseReleasedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseReleasedEvent: " << mouseCode;
        return ss.str();
    }

private:
    MouseCode mouseCode;
};


}
