#pragma once

#include "shadow/input/key_codes.h"

namespace Shadow {

class Input {
public:
    static bool IsKeyPressed(KeyCode key);
    static bool IsMouseButtonPressed(MouseCode button);
    static std::pair<float, float> GetMousePosition();
};

}
