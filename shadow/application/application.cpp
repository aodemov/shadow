#include "application.h"


namespace Shadow {

Application::Application()
    : eventBus(EventBus::get())
{
    window = std::make_unique<Window>(WindowOptions("Title"));
}

void Application::Init() {
    eventBus.addListener(&Application::OnEvent, this);
}

void Application::Run() {
    running = true;

    while(running) {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        window->OnUpdate();
    }
}

}