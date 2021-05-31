#pragma once

#include "shadow/ui/ui_block.h"

namespace Shadow {
class UiContainer : public UiBlock {
public:
    UiContainer() {
        mColor = {0.0f, 0.0f, 0.0f, 0.0f};
    }

    void SetSize(float screenWidth, float screenHeight) {
        box = {0, 0, screenWidth, screenHeight};
    }

    void Calculate() override {
        for (auto &child : mChildren) {
            child->Calculate();
        }
    }
};
}