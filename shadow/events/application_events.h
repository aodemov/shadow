#pragma once

#include "shadow/shpch.h"

#include "event.h"

namespace Shadow {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : mWidth(width), mHeight(height) {}

    unsigned int GetWidth() const { return mWidth; }
    unsigned int GetHeight() const { return mHeight; }

    const char* GetName() const override { return "WindowResizeEvent"; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << mWidth << "; " << mHeight;
        return ss.str();
    }
private:
    unsigned int mWidth, mHeight;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    const char* GetName() const override { return "WindowCloseEvent"; }
};



}