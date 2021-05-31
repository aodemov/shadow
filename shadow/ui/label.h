#pragma once

#include "shadow/renderer/font.h"

namespace Shadow {
class Label {
public:
    Label(std::string const &text, glm::vec2 const& position, Ref<Font> font, glm::vec4 const& color);

    inline std::string const& GetText() { return mText; }
    void SetText(std::string const &text) {
        mText = text;
        Calculate();
    }

    inline glm::vec2 const& GetPosition() { return mPosition; }
    void SetPosition(glm::vec2 const& position) {
        mPosition = position;
        Calculate();
    }

    void Draw();

private:
    std::string mText;
    glm::vec2 mPosition;
    Ref<Font> mFont;
    glm::vec4 mColor;

    void Calculate();
};
}