#pragma once

#include "Vector.h"
#include "Base/Json.h"

class Color
{
public:
	Color()
		: fRed(0.f), fGreen(0.f), fBlue(0.f) {}
	explicit Color(float r, float g, float b);
	explicit Color(int r, int g, int b);

public:
	float fRed;
	float fGreen;
	float fBlue;
};

namespace nlohmann
{
template<>
struct adl_serializer<Color>
{
	static void to_json(json& data, const Color& color)
	{
		data = json{
			{"r", color.fRed},
			{"g", color.fGreen},
			{"b", color.fBlue}
		};
	}
	static void from_json(const json& data, Color& color)
	{
		data.at("r").get_to(color.fRed);
		data.at("g").get_to(color.fGreen);
		data.at("b").get_to(color.fBlue);
	}
};
}