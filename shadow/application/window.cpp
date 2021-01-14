#include "window.h"

namespace Shadow {

static bool s_GLFWInitialized = false;

Window::Window(WindowOptions options)
    : options(options),
      window(nullptr),
      eventBus(EventBus::get())
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
    glfwSetWindowUserPointer(window, this);

    // Initializing callbacks
    glfwSetWindowCloseCallback(window, [](GLFWwindow* win) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.Shutdown();
        window.eventBus.emit(WindowCloseEvent());
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.options.Width = width;
        window.options.Height = height;

        window.eventBus.emit(WindowResizeEvent(width, height));
    });

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;

        switch (action) {
            case GLFW_PRESS:
                window.eventBus.emit(KeyPressedEvent(key, modifiers));
                break;
            case GLFW_RELEASE:
                window.eventBus.emit(KeyReleasedEvent(key, modifiers));
                break;
            case GLFW_REPEAT:
                window.eventBus.emit(KeyRepeatedEvent(key, modifiers));
                break;
        }
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;


        switch (action) {
            case GLFW_PRESS:
                window.eventBus.emit(MousePressedEvent(button, modifiers));
                break;
            case GLFW_RELEASE:
                window.eventBus.emit(MouseReleasedEvent(button, modifiers));
                break;
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double xOffset, double yOffset) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.eventBus.emit(MouseScrolledEvent(xOffset, yOffset));
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.eventBus.emit(MouseMovedEvent(x, y));
    });
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

void Window::Close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::IsClosed() const {
    return glfwWindowShouldClose(window);
}

void Window::Resize(unsigned int width, unsigned int height) {
    glfwSetWindowSize(window, width, height);
}

unsigned int Window::GetWidth() const {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

unsigned int Window::GetHeight() const {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

void Window::SetTitle(const std::string &title) {
    options.Title = title;
    glfwSetWindowTitle(window, title.c_str());
}

std::string Window::GetTitle() const {
    return options.Title;
}

void Window::Minimize() {
    glfwIconifyWindow(window);
}

void Window::Restore() {
    glfwRestoreWindow(window);
}

void Window::Maximize() {
    glfwMaximizeWindow(window);
}

bool Window::IsMinimized() const {
    return glfwGetWindowAttrib(window, GLFW_ICONIFIED);
}

bool Window::IsMaximized() const {
    return glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
}
}
