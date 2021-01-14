#pragma once

#include "shadow/shpch.h"

#include "event.h"

namespace Shadow {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : width(width), height(height) {}

    unsigned int GetWidth() const { return width; }
    unsigned int GetHeight() const { return height; }

    const char* GetName() const override { return "WindowResizeEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << "; " << height;
        return ss.str();
    }
private:
    unsigned int width, height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    const char* GetName() const override { return "WindowCloseEvent"; }
};



}