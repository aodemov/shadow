#include "debugger.h"

#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "shadow/application/game_loop.h"

namespace Shadow {


Debugger::Debugger() {

}

Debugger::~Debugger() {

}

void Debugger::Init() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplGlfw_InitForOpenGL(GameLoop::GetWindow().window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Debugger::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Debugger::Update(float delta) {
    auto& io = ImGui::GetIO();
    io.DeltaTime = delta;
    io.DisplaySize = ImVec2(GameLoop::GetWindow().GetWidth(), GameLoop::GetWindow().GetHeight());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
}