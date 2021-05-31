#include "label.h"

#include "shadow/renderer/render.h"

namespace Shadow {
Label::Label(const std::string &text, glm::vec2 const& position, Ref<Font> font, glm::vec4 const& color)
    : mText(text),
      mPosition(position),
      mFont(std::move(font)),
      mColor(color)
{
    Calculate();
}

void Label::Calculate() {
    float width = mFont->GetStringWidth(mText);
    mPosition.x -= width / 2;
}

void Label::Draw() {
    Render::DrawText(mText, { mPosition, 1.0f }, mFont, mColor);
}

}