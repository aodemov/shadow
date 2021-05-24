#include "window.h"

#ifdef SH_DEBUGGER
#include "shadow/core/debug/debugger.h"
#endif

namespace Shadow {

static bool s_GLFWInitialized = false;

Window::Window(WindowOptions options)
    : options(options),
      window(nullptr),
      eventBus(EventBus::Instance())
{
    if(options.VSync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

#ifdef SH_DEBUGGER
    Debugger::Stats.WindowTitle = options.Title;
    Debugger::Stats.VSync = options.VSync;
#endif
}

Window::~Window() {
}

void Window::Init() {
    SH_INFO("Initializing Window \"{0}\" ({1}, {2})", options.Title, options.Width, options.Height);

    if (!s_GLFWInitialized) {
        if(!glfwInit()) {
            SH_CORE_ERROR("Could not initialize GLFW");
            // TODO throw
        }

        s_GLFWInitialized = true;
    }

    window = glfwCreateWindow((int)options.Width, (int)options.Height, options.Title.c_str(), NULL, NULL);
    if(!window) {
        SH_CORE_ERROR("Could not create window");
        // TODO throw
    }

    context = std::make_unique<GraphicsContext>(window);
    context->Init();

    glfwSetWindowUserPointer(window, this);

    // Initializing callbacks
    glfwSetWindowCloseCallback(window, [](GLFWwindow* win) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.eventBus.push(WindowCloseEvent());
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.options.Width = width;
        window.options.Height = height;

#ifdef SH_DEBUGGER
    Debugger::Stats.WindowSize = { width, height };
#endif

        window.eventBus.push(WindowResizeEvent(width, height));
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
        glViewport(0, 0, width, height);

#ifdef SH_DEBUGGER
        Debugger::Stats.FrameSize = { width, height };
        Debugger::Stats.AspectRatio = (float)width / height;
#endif
    });

    glfwSetWindowIconifyCallback(window, [](GLFWwindow* win, int iconified) {
    });

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;

        switch (action) {
            case GLFW_PRESS:
                window.eventBus.push(KeyPressedEvent(key, modifiers));
                break;
            case GLFW_RELEASE:
                window.eventBus.push(KeyReleasedEvent(key, modifiers));
                break;
            case GLFW_REPEAT:
                window.eventBus.push(KeyRepeatedEvent(key, modifiers));
                break;
        }
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;


        switch (action) {
            case GLFW_PRESS:
                window.eventBus.push(MousePressedEvent(button, modifiers));
                break;
            case GLFW_RELEASE:
                window.eventBus.push(MouseReleasedEvent(button, modifiers));
                break;
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double xOffset, double yOffset) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.eventBus.push(MouseScrolledEvent(xOffset, yOffset));
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.eventBus.push(MouseMovedEvent(x, y));

#ifdef SH_DEBUGGER
        Debugger::Stats.MousePosition = { x, y };
#endif
    });

    // Error callback
    glfwSetErrorCallback([](int code, const char* message) {
        SH_CORE_ERROR("GLFW Error: {0} (code: {1})", message, code);
    });
}

void Window::Shutdown() {
    glfwDestroyWindow(window);

    if (s_GLFWInitialized) {
        glfwTerminate();
    }
}

void Window::Update() {
    glfwPollEvents();
    context->SwapBuffers();
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

float Window::GetAspectRatio() const {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
     return (float)width / height;
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
