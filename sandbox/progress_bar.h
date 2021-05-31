#pragma once

#include "shadow/shadow.h"

using namespace Shadow;

class ProgressBar : public UiBlock {
public:
    explicit ProgressBar(Ref<Font> font) {
        Color({ 0.5f, 0.5f, 0.5f, 1.0f });

        mLabel = MakeRef<Label>("0%", std::move(font), glm::vec4{ 1,1,1,1 });
        mLabel->CenterBoth();

        mLine = MakeRef<UiBlock>();
        mLine->MarginLeft(0).MarginTop(0).MarginBottom(0).Width(0).Color({1.0f, 0.0f, 0.0f, 1.0f});

        Add(mLine);
        Add(std::dynamic_pointer_cast<UiBlock, Label>(mLabel));
    }

    void SetValue(float value) {
        mValue = value;
        mLabel->SetText(std::to_string((int)mValue) + "%");
        mLine->Width(value, true);
        mLine->Calculate();
    }
private:
    float mValue = 0.0f;

    Ref<Label> mLabel;
    Ref<UiBlock> mLine;
};