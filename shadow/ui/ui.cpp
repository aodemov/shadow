#include "ui.h"

#include "shadow/application/application.h"
#include "shadow/input/input.h"

#include "shadow/ui/ui_container.h"

namespace Shadow {

struct UiData {
    Scope<Camera> UiCamera;
    glm::vec2 ScreenDimensions{0.0f};
    glm::vec2 MousePosition{0.0f};
    Ref<UiContainer> Container;
};

static UiData* uiData;

void UI::Init() {
    uiData = new UiData;

    uiData->ScreenDimensions = { Application::GetWindow().GetWidth(), Application::GetWindow().GetHeight() };
    uiData->UiCamera = MakeScope<Camera>(0, uiData->ScreenDimensions.x, uiData->ScreenDimensions.y, 0);

    uiData->Container = MakeRef<UiContainer>();
    uiData->Container->SetSize(uiData->ScreenDimensions.x, uiData->ScreenDimensions.y);

    Application::GetEventBus().AddListener<WindowResizeEvent>([&](auto e){
        uiData->ScreenDimensions = { e.GetWidth(), e.GetHeight() };
        uiData->UiCamera->SetProjection(0, e.GetWidth(), e.GetHeight(), 0);

        uiData->Container->SetSize(uiData->ScreenDimensions.x, uiData->ScreenDimensions.y);
        uiData->Container->Calculate();
    });
}

void UI::Shutdown() {
    delete uiData;
}

void UI::Begin() {
    Render::BeginScene(*uiData->UiCamera);
    uiData->MousePosition = Input::GetMousePosition();
    uiData->Container->Draw();
}

void UI::End() {
    Render::EndScene();
}

void UI::Add(Ref<UiBlock> block) {
    uiData->Container->Add(std::move(block));
}

}