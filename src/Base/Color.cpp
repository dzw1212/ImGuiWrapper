#include "Color.h"
#include <algorithm>


Color::Color(float r, float g, float b)
{
    fRed = std::clamp(r, 0.f, 1.f);
    fGreen = std::clamp(g, 0.f, 1.f);
    fBlue = std::clamp(b, 0.f, 1.f);
}

Color::Color(int r, int g, int b)
{
    fRed = static_cast<float>(std::clamp(r, 0, 255) / 255.f);
    fGreen = static_cast<float>(std::clamp(g, 0, 255) / 255.f);
    fBlue = static_cast<float>(std::clamp(b, 0, 255) / 255.f);
}

