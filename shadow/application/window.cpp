#include "window.h"

namespace Shadow {

static bool s_GLFWInitialized = false;

Window::Window(WindowOptions options)
    : options(options),
      window(nullptr)
{
    if(options.VSync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    Init();
}

Window::~Window() {
    Shutdown();
}

void Window::Init() {
    SH_INFO("Initializing Window \"{0}\" ({1}, {2})", options.Title, options.Width, options.Height);

    if (!s_GLFWInitialized) {
        if(!glfwInit()) {
            SH_ERROR("Could not initialize GLFW");
            // TODO throw
        }

        s_GLFWInitialized = true;
    }

    window = glfwCreateWindow((int)options.Width, (int)options.Height, options.Title.c_str(), NULL, NULL);
    if(!window) {
        SH_ERROR("Could not create window");
        // TODO throw
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

}

void Window::Shutdown() {
    glfwDestroyWindow(window);

    if (s_GLFWInitialized) {
        glfwTerminate();
    }
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

}
