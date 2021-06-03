#pragma once

#include "shadow/shpch.h"

#include "event.h"
#include "shadow/input/key_codes.h"

namespace Shadow {

class KeyPressedEvent : public Event {
public:
    explicit KeyPressedEvent(const KeyCode keyCode, const KeyModifiers mods = Modifiers::None)
        : mKeyCode(keyCode),
          mMods(mods) {}

    KeyCode GetKeyCode() const { return mKeyCode; }
    KeyModifiers GetModifiers() const { return mMods; }

    EventType GetType() const override { return Event::KeyPressed; }
    static EventType GetStaticType() { return Event::KeyPressed; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << mKeyCode;
        return ss.str();
    }

private:
    KeyCode mKeyCode;
    KeyModifiers mMods;
};

class KeyReleasedEvent : public Event {
public:
    explicit KeyReleasedEvent(const KeyCode keyCode, const KeyModifiers mods = Modifiers::None)
        : mKeyCode(keyCode),
          mMods(mods) {}

    KeyCode GetKeyCode() const { return mKeyCode; }
    KeyModifiers GetModifiers() const { return mMods; }

    EventType GetType() const override { return Event::KeyReleased; }
    static EventType GetStaticType() { return Event::KeyReleased; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << mKeyCode;
        return ss.str();
    }

private:
    KeyCode mKeyCode;
    KeyModifiers mMods;
};

class KeyRepeatedEvent : public Event {
public:
    explicit KeyRepeatedEvent(const KeyCode keyCode, const KeyModifiers mods = Modifiers::None)
        : mKeyCode(keyCode),
          mMods(mods) {}

    KeyCode GetKeyCode() const { return mKeyCode; }
    KeyModifiers GetModifiers() const { return mMods; }

    EventType GetType() const override { return Event::KeyRepeated; }
    static EventType GetStaticType() { return Event::KeyRepeated; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyRepeatedEvent: " << mKeyCode;
        return ss.str();
    }

private:
    KeyCode mKeyCode;
    KeyModifiers mMods;
};

}
