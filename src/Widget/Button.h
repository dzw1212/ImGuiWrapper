#pragma once
#include "Widget.h"

#include "Base/Color.h"

#include <string>
#include <functional>
#include <unordered_map>

enum eButtonMouse_
{
	eButtonMouse_None,
	eButtonMouse_Left,
	eButtonMouse_Right,
	eButtonMouse_Middle,
	eButtonMouse_Count,
};

class Button : public Widget
{
public:
	Button() 
		: Widget() {}
	Button(const std::string& content)
		: m_strContent(content), Widget() {}

	virtual void Draw() override;
	virtual std::string GetTypeName() const override { return "Button"; }
	virtual void Serialize(Json& data) override;
	virtual void Deserialize(const Json& data) override;
	void SetClickFunc(std::function<void(void)> func, eButtonMouse_ button);

private:
	std::string m_strContent;
	std::unordered_map<eButtonMouse_, std::function<void(void)>> m_mapClickFunc;
};