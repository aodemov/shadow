#pragma once

#include <glm/vec2.hpp>

#include "shadow/input/key_codes.h"

namespace Shadow {

class Input {
public:
    static bool IsKeyPressed(KeyCode key);
    static bool IsMouseButtonPressed(MouseCode button);
    static glm::vec2 GetMousePosition();
};

}
