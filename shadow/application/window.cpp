#include "window.h"

#ifdef SH_DEBUGGER
#include "shadow/core/debug/debugger.h"
#endif

namespace Shadow {

static bool s_GLFWInitialized = false;

Window::Window(WindowOptions options)
    : mOptions(options),
      mWindow(nullptr),
      mEventBus(EventBus::Instance())
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
    SH_INFO("Initializing Window \"{0}\" ({1}, {2})", mOptions.Title, mOptions.Width, mOptions.Height);

    if (!s_GLFWInitialized) {
        if(!glfwInit()) {
            SH_CORE_ERROR("Could not initialize GLFW");
            // TODO throw
        }

        s_GLFWInitialized = true;
    }

    mWindow = glfwCreateWindow((int)mOptions.Width, (int)mOptions.Height, mOptions.Title.c_str(), NULL, NULL);
    if(!mWindow) {
        SH_CORE_ERROR("Could not create window");
        // TODO throw
    }

    mContext = std::make_unique<GraphicsContext>(mWindow);
    mContext->Init();

    glfwSetWindowUserPointer(mWindow, this);

    // Initializing callbacks
    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* win) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.mEventBus.Push(WindowCloseEvent());
    });

    glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* win, int width, int height){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.mOptions.Width = width;
        window.mOptions.Height = height;

#ifdef SH_DEBUGGER
    Debugger::Stats.WindowSize = { width, height };
#endif

        window.mEventBus.Push(WindowResizeEvent(width, height));
    });

    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* win, int width, int height) {
        glViewport(0, 0, width, height);

#ifdef SH_DEBUGGER
        Debugger::Stats.FrameSize = { width, height };
        Debugger::Stats.AspectRatio = (float)width / height;
#endif
    });

    glfwSetWindowIconifyCallback(mWindow, [](GLFWwindow* win, int iconified) {
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;

        switch (action) {
            case GLFW_PRESS:
                window.mEventBus.Push(KeyPressedEvent(key, modifiers));
                break;
            case GLFW_RELEASE:
                window.mEventBus.Push(KeyReleasedEvent(key, modifiers));
                break;
            case GLFW_REPEAT:
                window.mEventBus.Push(KeyRepeatedEvent(key, modifiers));
                break;
        }
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* win, int button, int action, int mods){
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        KeyModifiers modifiers = mods;


        switch (action) {
            case GLFW_PRESS:
                window.mEventBus.Push(MousePressedEvent(button, modifiers));
                break;
            case GLFW_RELEASE:
                window.mEventBus.Push(MouseReleasedEvent(button, modifiers));
                break;
        }
    });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* win, double xOffset, double yOffset) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.mEventBus.Push(MouseScrolledEvent(xOffset, yOffset));
    });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* win, double x, double y) {
        Window& window = *(Window*)glfwGetWindowUserPointer(win);
        window.mEventBus.Push(MouseMovedEvent(x, y));

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
    glfwDestroyWindow(mWindow);

    if (s_GLFWInitialized) {
        glfwTerminate();
    }
}

void Window::Update() {
    glfwPollEvents();
    mContext->SwapBuffers();
}

void Window::Close() {
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

bool Window::IsClosed() const {
    return glfwWindowShouldClose(mWindow);
}

void Window::Resize(unsigned int width, unsigned int height) {
    glfwSetWindowSize(mWindow, width, height);
}

unsigned int Window::GetWidth() const {
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return width;
}

unsigned int Window::GetHeight() const {
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return height;
}

float Window::GetAspectRatio() const {
    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);
     return (float)width / height;
}

void Window::SetTitle(const std::string &title) {
    mOptions.Title = title;
    glfwSetWindowTitle(mWindow, title.c_str());
}

std::string Window::GetTitle() const {
    return mOptions.Title;
}

void Window::Minimize() {
    glfwIconifyWindow(mWindow);
}

void Window::Restore() {
    glfwRestoreWindow(mWindow);
}

void Window::Maximize() {
    glfwMaximizeWindow(mWindow);
}

bool Window::IsMinimized() const {
    return glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED);
}

bool Window::IsMaximized() const {
    return glfwGetWindowAttrib(mWindow, GLFW_MAXIMIZED);
}
}
