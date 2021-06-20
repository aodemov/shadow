#include "debugger.h"

#include <lib/imgui/imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "shadow/application/application.h"

namespace Shadow {

Debugger::Debugger() = default;

Debugger::~Debugger() = default;

void Debugger::Show() {
    mVisible = true;
}

void Debugger::Hide() {
    mVisible = false;
}

void Debugger::Init() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow().mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    mEventBus.AddListener<KeyPressedEvent>([&](auto& e) {
       if (e.GetKeyCode() == Key::F3) {
            mVisible = !mVisible;
       } else if (e.GetKeyCode() == Key::F4) {
           Props.ShowColliders = Props.ShowTriggers = !Props.ShowColliders;
       }
    });
}

void Debugger::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Debugger::Update(float delta) {
    if (!mVisible)
        return;

    static float elapsedTime = 0.0f;
    static float smoothFrameTime = 1.0f;
    elapsedTime += Stats.FrameTime;
    if (Stats.ElapsedFrames % 10 == 0) {
        smoothFrameTime = elapsedTime / 10;
        elapsedTime = 0;
    }

    auto& io = ImGui::GetIO();
    io.DeltaTime = delta;
    io.DisplaySize = ImVec2((float)Application::GetWindow().GetWidth(), (float)Application::GetWindow().GetHeight());


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::Begin("Debug", nullptr, (ImGuiWindowFlags)43);

    ImGui::Text("Renderer Stats: ");
    ImGui::Text("Draw Calls: %d", Stats.DrawCalls);
    ImGui::Text("Rect Count: %d", Stats.RectCount);
    ImGui::Text("Texture Slots Used: %d", Stats.TextureCount);
    ImGui::Separator();

    ImGui::Text("FPS: %d (%fms.)", (int)(1.0f / smoothFrameTime), smoothFrameTime);
    ImGui::Text("Fixed Update Time: %fms.", Stats.FixedUpdateTime);
    ImGui::Text("Variable Update Time: %fms.", Stats.VariableUpdateTime);
    ImGui::Text("Fixed FPS: %d", Stats.FixedFPS);
    ImGui::Text("Elapsed Time: %fs.", Stats.ElapsedTime);
    ImGui::Text("Elapsed Frames: %d: ", Stats.ElapsedFrames);
    ImGui::Separator();

    ImGui::Text("Window Stats:");
    ImGui::Text("Window Size: %dx%d", (int)Stats.WindowSize.x, (int)Stats.WindowSize.y);
    ImGui::Text("Frame  Size: %dx%d", (int)Stats.FrameSize.x, (int)Stats.FrameSize.y);
    ImGui::Text("Aspect Ratio: %f", Stats.AspectRatio);
    ImGui::Text("Fullscreen: %s", Stats.Fullscreen ? "true" : "false");
    ImGui::Text("VSync: %s", Stats.VSync ? "true" : "false");
    ImGui::Text("Window Title: %s", Stats.WindowTitle.c_str());
    ImGui::Separator();

    ImGui::Text("Events: ");
    ImGui::Text("Mouse Position: %d,%d", (int)Stats.MousePosition.x, (int)Stats.MousePosition.y);
    ImGui::Separator();

    ImGui::Text("Constants: ");
    ImGui::Text("Max Rects: %d", Stats.MaxRects);
    ImGui::Text("Max Texture Slots: %d", Stats.MaxTextureSlots);

    ImGui::Separator();

    ImGui::Checkbox("Show colliders: ", &Props.ShowColliders);
    ImGui::Checkbox("Show triggers: ", &Props.ShowTriggers);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    Stats.Reset();
}
}