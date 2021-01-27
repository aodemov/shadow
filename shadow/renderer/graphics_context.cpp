#include "graphics_context.h"

namespace Shadow {

GraphicsContext::GraphicsContext(GLFWwindow *window)
    : window(window) {}

void GraphicsContext::Init() {
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
}

void GraphicsContext::SwapBuffers() {
    glfwSwapBuffers(window);
}

}