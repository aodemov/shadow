#pragma once

#include "shadow/events/mouse_events.h"
#include "shadow/events/keyboard_events.h"

namespace Shadow {

inline bool isInBox(float x, float y, glm::vec4 const& box) {
    return (x >= box.x) && (x <= box.p) && (y >= box.y) && (y <= box.q);
}

class UiBlock {
public:
    UiBlock() = default;
    ~UiBlock() = default;

    virtual void Calculate();
    virtual void Draw();

    std::vector<Ref<UiBlock>>& GetChildren() { return mChildren; }
    void Add(Ref<UiBlock> child);

    UiBlock& MarginLeft  (float value, bool percent = false) { margins.x = percent ? -value : value; return *this; }
    UiBlock& MarginTop   (float value, bool percent = false) { margins.y = percent ? -value : value; return *this; }
    UiBlock& MarginRight (float value, bool percent = false) { margins.p = percent ? -value : value; return *this; }
    UiBlock& MarginBottom(float value, bool percent = false) { margins.q = percent ? -value : value; return *this; }

    UiBlock& FillParent() { margins = { 0, 0, 0, 0}; return *this; }

    UiBlock& Width (float value, bool percent = false) { size.x = percent ? -value : value; return *this; }
    UiBlock& Height(float value, bool percent = false) { size.y = percent ? -value : value; return *this; }

    UiBlock& CenterX(bool value = true) { ch = value; return *this; }
    UiBlock& CenterY(bool value = true) { cv = value; return *this; }
    UiBlock& CenterBoth(bool value = true) { cv = ch = value; return *this; }

    UiBlock& Color(glm::vec4 const& color) { mColor = color; return *this; }
protected:
    glm::vec4 box {0.0f};
    glm::vec4 mColor {1.0f};

    std::vector<Ref<UiBlock>> mChildren;

    virtual bool OnEvent(const Event* e);
private:
    glm::vec4 margins {1e7};
    glm::vec2 size {1e7};
    bool ch = false, cv = false;
    UiBlock* parent = nullptr;
};
}