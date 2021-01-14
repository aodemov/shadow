#pragma once

#include "shadow/shpch.h"

#include "event.h"
#include "shadow/core/input/key_codes.h"

namespace Shadow {

class KeyPressedEvent : public Event {
public:
    KeyPressedEvent(const KeyCode keyCode, const KeyModifiers = Modifiers::None)
        : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }
    KeyModifiers GetModifiers() const { return mods; }

    const char* GetName() const override { return "KeyPressedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << keyCode;
        return ss.str();
    }

private:
    KeyCode keyCode;
    KeyModifiers mods;
};

class KeyReleasedEvent : public Event {
public:
    KeyReleasedEvent(const KeyCode keyCode, const KeyModifiers = Modifiers::None)
            : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }
    KeyModifiers GetModifiers() const { return mods; }

    const char* GetName() const override { return "KeyReleasedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << keyCode;
        return ss.str();
    }

private:
    KeyCode keyCode;
    KeyModifiers mods;
};

class KeyRepeatedEvent : public Event {
public:
    KeyRepeatedEvent(const KeyCode keyCode, const KeyModifiers = Modifiers::None)
            : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }
    KeyModifiers GetModifiers() const { return mods; }

    const char* GetName() const override { return "KeyRepeatedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyRepeatedEvent: " << keyCode;
        return ss.str();
    }

private:
    KeyCode keyCode;
    KeyModifiers mods;
};

}
