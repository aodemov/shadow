#pragma once

namespace Shadow {

class Event {
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

}
