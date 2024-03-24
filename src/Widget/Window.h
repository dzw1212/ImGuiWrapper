#pragma once

#include "Widget.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>


class Window : public Widget
{
public:
	Window() 
		: Widget() {}
	Window(const std::string& name)
		: m_strName(name), Widget() {}

	void AddChild(std::shared_ptr<Widget> widget);
	virtual void Draw() override;
	virtual std::string GetTypeName() const override { return "Window"; }
	virtual void Serialize(Json& data) override;
	virtual void Deserialize(const Json& data) override;
private:
	std::string m_strName;
	std::vector<std::shared_ptr<Widget>> m_vecWidgets;
	std::unordered_map<UUID, std::shared_ptr<Widget>> m_mapWidgets;
};