#pragma once

#include "shadow/ui/ui_block.h"
#include "shadow/renderer/camera.h"

namespace Shadow {
class UiContainer : public UiBlock {
public:
    UiContainer() {
        mColor = {0.0f, 0.0f, 0.0f, 0.0f};
        mUiCamera = MakeRef<Camera>(0, mScreenDimensions.x, mScreenDimensions.y, 0);
    }

    UiContainer(const UiContainer& other) = default;

    void SetSize(float screenWidth, float screenHeight) {
        mScreenDimensions = { screenWidth, screenHeight };
        box = {0, 0, screenWidth, screenHeight};
        mUiCamera->SetProjection(0, mScreenDimensions.x, mScreenDimensions.y, 0);
        Calculate();
    }

    void Calculate() override {
        for (auto &child : mChildren) {
            child->Calculate();
        }
    }

private:
    friend class Scene;
    Ref<Camera> mUiCamera{};
    glm::vec2 mScreenDimensions{0.0f};
};
}