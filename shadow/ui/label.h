#pragma once

#include "shadow/renderer/font.h"
#include "shadow/ui/ui_block.h"

namespace Shadow {
class Label : public UiBlock {
public:
    Label(std::string const &text, Ref<Font> font, glm::vec4 const& color);

    inline std::string const& GetText() { return mText; }
    void SetText(std::string const &text) {
        mText = text;
        Calculate();
    }

    void Draw() override;
    void Calculate() override;

private:
    std::string mText;
    Ref<Font> mFont;
    glm::vec4 mColor;
};
}