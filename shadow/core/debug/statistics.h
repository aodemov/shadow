#pragma once

namespace Shadow {
struct Statistics {
    // Render
    uint32_t DrawCalls = 0;
    uint32_t RectCount = 0;
    uint32_t TextureCount = 0;

    // Frame time
    float FixedUpdateTime = 0;
    float VariableUpdateTime = 0;
    float FrameTime = 0.0f;
    uint32_t ElapsedFrames = 0;
    double ElapsedTime = 0;
    uint32_t FixedFPS = 0;

    // Window
    glm::vec2 WindowSize{0.0f};
    glm::vec2 FrameSize{0.0f};
    float AspectRatio = 0.0f;
    bool Fullscreen = false;
    bool VSync = true;
    std::string WindowTitle;

    // Events
    glm::vec2 MousePosition{0.0f};

    // Consts
    uint32_t MaxRects = 0;
    uint32_t MaxTextureSlots = 0;

    Statistics() noexcept = default;

    void Reset() {
        DrawCalls = 0;
        RectCount = 0;
        TextureCount = 0;
    }
};
}
