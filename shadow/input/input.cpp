#include "input.h"
#include "shadow/application/game_loop.h"

namespace Shadow {

bool Input::IsKeyPressed(KeyCode key) {
    auto window = GameLoop::GetWindow().window;

    int state = glfwGetKey(window, key);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
    auto window = GameLoop::GetWindow().window;

    int state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition() {
    auto window = GameLoop::GetWindow().window;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return std::make_pair(static_cast<float>(x), static_cast<float>(y));
}
}