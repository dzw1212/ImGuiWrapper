#pragma once
#include <string>
#include <format>
#include "Base/UUID.h"
#include "Base/Json.h"

class Widget
{
public:
	Widget() {}
	virtual ~Widget() {}

	virtual void Draw() = 0;
	virtual std::string GetTypeName() const = 0;
	virtual void Serialize(Json& data) = 0;
	virtual void Deserialize(const Json& data) = 0;

	std::string GetUniqueName() const { return std::format("{0}-{1}", GetTypeName(), m_ID.m_u64Id); }
public:
	UUID m_ID;
};