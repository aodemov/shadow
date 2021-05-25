#include "graphics_context.h"

namespace Shadow {

GraphicsContext::GraphicsContext(GLFWwindow *window)
    : mWindow(window) {}

void GraphicsContext::Init() {
    glfwMakeContextCurrent(mWindow);
    gladLoadGL(glfwGetProcAddress);
}

void GraphicsContext::SwapBuffers() {
    glfwSwapBuffers(mWindow);
}

}