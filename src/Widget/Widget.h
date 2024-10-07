#pragma once
#include <string>
#include <format>
#include "Base/UUID.h"
#include "Base/Json.h"
#include "Base/Vector.h"

struct Layout
{
	Vector2 Pivot;
	Vector2 Anchor;
	Vector2 Pos;
	bool bValid = false;
};

class Widget
{
public:
	Widget() {}
	virtual ~Widget() {}

	virtual void Draw() = 0;
	virtual std::string GetTypeName() const = 0;
	virtual void Serialize(Json& data) = 0;
	virtual void Deserialize(const Json& data) = 0;

	void SetPivot(float x, float y)
	{
		m_Layout.bValid = true;
		m_Layout.Pivot.x = std::clamp(x, 0.f, 1.f);
		m_Layout.Pivot.y = std::clamp(y, 0.f, 1.f);
	}
	void SetAnchor(float x, float y)
	{
		m_Layout.bValid = true;
		m_Layout.Anchor.x = std::clamp(x, 0.f, 1.f);
		m_Layout.Anchor.y = std::clamp(y, 0.f, 1.f);
	}
	void SetPos(float x, float y)
	{
		m_Layout.bValid = true;
		m_Layout.Pos.x = x;
		m_Layout.Pos.y = y;
	}

	std::string GetUniqueName() const { return std::format("{0}-{1}", GetTypeName(), m_ID.m_u64Id); }
public:
	UUID m_ID;
	Layout m_Layout;
};