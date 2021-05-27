#include "borders.h"

#include "shadow.h"
using namespace Shadow;


Borders::Borders(float width, float height)
    : width(width), height(height)
{
    borders.emplace_back(glm::vec2(-width / 2, -height / 2));
    borders.emplace_back(glm::vec2(-width / 2,  height / 2));
    borders.emplace_back(glm::vec2( width / 2,  height / 2));
    borders.emplace_back(glm::vec2( width / 2, -height / 2));
}

void Borders::Draw() {
    const float borderWidth = 0.3f;
    const glm::vec4 borderColor = { 0, 0, 0, 0.8f };
    auto& bc = GetCorners();
    Render::DrawLine(bc[0], bc[1], borderWidth, borderColor);
    Render::DrawLine(bc[1], bc[2], borderWidth, borderColor);
    Render::DrawLine(bc[2], bc[3], borderWidth, borderColor);
    Render::DrawLine(bc[3], bc[0], borderWidth, borderColor);
}
