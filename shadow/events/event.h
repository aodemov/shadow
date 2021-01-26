#pragma once

namespace Shadow {

class Event {
public:
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

}
