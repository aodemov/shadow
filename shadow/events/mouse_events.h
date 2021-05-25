#pragma once

#include "event.h"
#include "shadow/input/key_codes.h"

namespace Shadow {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const double x, const double y)
            : mX(x), mY(y) {}

    double GetX() const { return mX; }
    double GetY() const { return mY; }

    const char* GetName() const override { return "MouseMovedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << mX << "; " << mY;
        return ss.str();
    }

private:
    double mX, mY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const double xOffset, const double yOffset)
            : mX(xOffset), mY(yOffset) {}

    double GetXOffset() const { return mX; }
    double GetYOffset() const { return mY; }

    const char* GetName() const override { return "MouseScrolledEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << mX << "; " << mY;
        return ss.str();
    }

private:
    double mX, mY;
};

class MousePressedEvent : public Event {
public:
    MousePressedEvent(const MouseCode mouseCode, const KeyModifiers = Modifiers::None)
            : mMouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mMouseCode; }
    KeyModifiers GetModifiers() const { return mMods; }

    const char* GetName() const override { return "MousePressedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MousePressedEvent: " << mMouseCode;
        return ss.str();
    }

private:
    MouseCode mMouseCode;
    KeyModifiers mMods;
};

class MouseReleasedEvent : public Event {
public:
    MouseReleasedEvent(const MouseCode mouseCode, const KeyModifiers = Modifiers::None)
            : mMouseCode(mouseCode) {}

    MouseCode GetMouseCode() const { return mMouseCode; }
    KeyModifiers GetModifiers() const { return mMods; }

    const char* GetName() const override { return "MouseReleasedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseReleasedEvent: " << mMouseCode;
        return ss.str();
    }

private:
    MouseCode mMouseCode;
    KeyModifiers mMods;
};


}
