#pragma once

#include "shadow/shpch.h"

#include "event.h"
#include "shadow/core/input/key_codes.h"

namespace Shadow {

class KeyPressedEvent : public Event {
public:
    KeyPressedEvent(const KeyCode keyCode)
        : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }

    const char* GetName() const override { return "KeyPressedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << keyCode;
        return ss.str();
    }

private:
    uint16_t keyCode;
};

class KeyReleasedEvent : public Event {
public:
    KeyReleasedEvent(const KeyCode keyCode)
            : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }

    const char* GetName() const override { return "KeyReleasedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << keyCode;
        return ss.str();
    }

private:
    uint16_t keyCode;
};

class KeyRepeatedEvent : public Event {
public:
    KeyRepeatedEvent(const KeyCode keyCode)
            : keyCode(keyCode) {}

    KeyCode GetKeyCode() const { return keyCode; }

    const char* GetName() const override { return "KeyRepeatedEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyRepeatedEvent: " << keyCode;
        return ss.str();
    }

private:
    uint16_t keyCode;
};

}
