#include "ui.h"

#include "shadow/application/application.h"

namespace Shadow {

static inline Camera* uiCamera;

void UI::Init() {
    uiCamera = new Camera(0, Application::GetWindow().GetWidth(), Application::GetWindow().GetHeight(), 0);

    Application::GetEventBus().AddListener<WindowResizeEvent>([&](auto e){
        uiCamera->SetProjection(0, e.GetWidth(), e.GetHeight(), 0);
    });
}

void UI::Shutdown() {
    delete uiCamera;
}

void UI::Begin() {
    Render::BeginScene(*uiCamera);
}

void UI::End() {
    Render::EndScene();
}

}