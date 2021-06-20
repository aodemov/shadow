#include "ui_block.h"

#include "shadow/renderer/render.h"

namespace Shadow {
inline bool isSet(float v) {
    return v < 1e6;
}
inline bool isRel(float v) {
    return v < 0 && isSet(v);
}

void UiBlock::Calculate() {
    float vw = parent->box.p - parent->box.x;
    float vh = parent->box.q - parent->box.y;

    glm::vec4 m = margins;
    glm::vec2 s = size;
    // Translating relative values to absolute
    if (isRel(m.x))
        m.x = (-m.x) / 100.0f * vw;
    if (isRel(m.y))
        m.y = (-m.y) / 100.0f * vh;
    if (isRel(m.p))
        m.p = (-m.p) / 100.0f * vw;
    if (isRel(m.q))
        m.q = (-m.q) / 100.0f * vh;
    if (isRel(s.x))
        s.x = (-s.x) / 100.0f * vw;
    if (isRel(s.y))
        s.y = (-s.y) / 100.0f * vh;


    if (ch) {
        float offsetX = 0;
        if (isSet(m.x))
            offsetX += m.x;
        if (isSet(m.p))
            offsetX -= m.p;

        m.x = m.p = (vw - s.x) / 2.0f;
        m.x += offsetX;
        m.p -= offsetX;
    }

    if (cv) {
        float offsetY = 0;
        if (isSet(m.y))
            offsetY += m.y;
        if (isSet(m.q))
            offsetY -= m.q;

        m.y = m.q = (vh - s.y) / 2.0f;
        m.y += offsetY;
        m.q -= offsetY;
    }

    if (!isSet(m.x)) // left padding
        m.x = vw - m.p - s.x;
    if (!isSet(m.y))
        m.y = vh - m.q - s.y;
    if (!isSet(m.p))
        m.p = vw - m.x - s.x;
    if (!isSet(m.q))
        m.q = vh - m.y - s.y;

    box = { parent->box.x + m.x, parent->box.y +  m.y, parent->box.x +  vw - m.p, parent->box.y +  vh - m.q };

    for (auto& child : mChildren) {
        child->Calculate();
    }
}

void UiBlock::Draw() {
    for (auto& child : mChildren) {
        child->Draw();
    }
    Render::DrawRect(box, mColor);
}

void UiBlock::Add(Ref<UiBlock> child) {
    child->parent = this;

    mChildren.push_back(std::move(child));
}

bool UiBlock::OnEvent(const Event *e) {
    for (auto& child : mChildren) {
        if (child->OnEvent(e))
            return true;
    }
    return false;
}
}
