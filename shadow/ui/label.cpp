#include "label.h"

#include "shadow/renderer/render.h"

namespace Shadow {
Label::Label(const std::string &text, Ref<Font> font, glm::vec4 const& color)
    : mText(text),
      mFont(std::move(font)),
      mColor(color) {}

void Label::Calculate() {
    float width = mFont->GetStringWidth(mText);
    float height = mFont->GetSize();
    Width(width);
    Height(height);
    UiBlock::Calculate();
}

void Label::Draw() {
    Render::DrawText(mText, { box.x, box.q + mFont->GetDescent(), 1.0f }, mFont, mColor);
}

}