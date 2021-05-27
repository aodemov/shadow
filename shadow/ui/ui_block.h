#pragma once

namespace Shadow {
class UIBlock {
public:
    UIBlock() = default;
    ~UIBlock() = default;

    void Calculate(float vw, float vh);
    void Draw();

    UIBlock& MarginLeft  (float value, bool percent = false) { margins.x = percent ? -value : value; return *this; }
    UIBlock& MarginTop   (float value, bool percent = false) { margins.y = percent ? -value : value; return *this; }
    UIBlock& MarginRight (float value, bool percent = false) { margins.p = percent ? -value : value; return *this; }
    UIBlock& MarginBottom(float value, bool percent = false) { margins.q = percent ? -value : value; return *this; }

    UIBlock& Width (float value, bool percent = false) { size.x = percent ? -value : value; return *this; }
    UIBlock& Height(float value, bool percent = false) { size.y = percent ? -value : value; return *this; }

    UIBlock& CenterX(bool value = true) { ch = value; return *this; }
    UIBlock& CenterY(bool value = true) { cv = value; return *this; }
    UIBlock& CenterBoth(bool value = true) { cv = ch = value; return *this; }
private:
    glm::vec4 box;
    glm::vec4 margins {1e7};
    glm::vec2 size {1e7};
    bool ch = false, cv = false;
};
}