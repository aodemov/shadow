#pragma once

#include "shadow.h"

using namespace Shadow;

class Scoreboard : public UiBlock {
public:
    Scoreboard() {
        Color({ 0, 0, 0, 0.2f });

        mLabel = MakeRef<Label>("", MakeRef<Font>("assets/segoeui.ttf", 40), glm::vec4{ 0, 0, 0, 1 });
        mLabel->MarginLeft(10).MarginTop(60);
        Add(mLabel);

        auto title = MakeRef<Label>("Scoreboard:", MakeRef<Font>("assets/segoeui.ttf", 60), glm::vec4{ 0, 0, 0, 1 });
        title->MarginTop(10).MarginLeft(10);
        Add(title);
    }

    void SetScore(int score) {
        mScore = score;
        mLabel->SetText("Player: " + std::to_string(mScore));
    }
private:
    int mScore = 0;
    Ref<Label> mLabel;
};