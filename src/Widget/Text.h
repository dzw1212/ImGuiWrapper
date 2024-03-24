#pragma once

#include <string>
#include "Base/Color.h"
#include "Base/UUID.h"
#include "Widget.h"

enum eTextFlags_
{
	eTextFlags_None = 0,
	eTextFlags_Color,
	eTextFlags_Label,
	eTextFlags_Bulletin,
	eTextFlags_Unformatted,
	eTextFlags_Disable,
	eTextFlags_Wrapped,
	eTextFlags_Separator,
	eTextFlags_Count,
};

class Text : public Widget
{
public:
	Text() 
		: Widget() {}
	Text(const std::string& content, eTextFlags_ flags = eTextFlags_None)
		: m_strContent(content), m_Flags(flags), Widget()
	{}
	void SetColor(const Color& color) { m_Color = color; }
	virtual void Draw() override;
	virtual std::string GetTypeName() const override { return "Text"; }
	virtual void Serialize(Json& data) override;
	virtual void Deserialize(const Json& data) override;
private:
	std::string m_strContent;
	Color m_Color;
	eTextFlags_ m_Flags = eTextFlags_None;
};