#include "borders.h"

Borders::Borders(float width, float height)
    : width(width), height(height)
{
    borders.emplace_back(glm::vec2(-width / 2, -height / 2));
    borders.emplace_back(glm::vec2(-width / 2,  height / 2));
    borders.emplace_back(glm::vec2( width / 2,  height / 2));
    borders.emplace_back(glm::vec2( width / 2, -height / 2));
}
