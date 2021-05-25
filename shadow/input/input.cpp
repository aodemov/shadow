#include "input.h"
#include "shadow/application/application.h"

namespace Shadow {

bool Input::IsKeyPressed(KeyCode key) {
    auto window = Application::GetWindow().mWindow;

    int state = glfwGetKey(window, key);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
    auto window = Application::GetWindow().mWindow;

    int state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
    auto window = Application::GetWindow().mWindow;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return { static_cast<float>(x), static_cast<float>(y) };
}
}