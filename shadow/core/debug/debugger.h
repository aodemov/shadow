#pragma once

namespace Shadow {
class Debugger {
public:
    Debugger();
    ~Debugger();

    void Init();
    void Shutdown();

    void Update(float delta);
private:

};
}
