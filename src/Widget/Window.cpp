#include "Window.h"
#include "WidgetFactory.h"
#include "Base/Log.h"

#include "imgui.h"

void Window::AddChild(std::shared_ptr<Widget> widget)
{
	if (m_mapWidgets.find(widget->m_ID) != m_mapWidgets.end())
	{
		Log::Error("Dup Widget ID {}", static_cast<uint64_t>(widget->m_ID));
		return;
	}
	m_mapWidgets[widget->m_ID] = widget;
	m_vecWidgets.push_back(widget);
}

void Window::Draw()
{
	ImGui::Begin(m_strName.c_str());

	for (auto& widget : m_vecWidgets)
	{
		widget->Draw();
	}

	ImGui::End();
}

void Window::Serialize(Json& data)
{
	Json children;
	for (auto& widget : m_vecWidgets)
	{
		Json child;
		widget->Serialize(child);
		children[widget->GetUniqueName()] = child;
	}
	data = Json{
		{"name", m_strName},
		{"type", GetTypeName()},
		{"children", children},
		{"uuid", m_ID},
	};
}

void Window::Deserialize(const Json& data)
{
	data.at("name").get_to(m_strName);
	data.at("uuid").get_to(m_ID);
	m_vecWidgets.clear();
	m_mapWidgets.clear();
	for (auto& it : data.at("children"))
	{
		auto& strType = it.at("type");
		if (strType == "Text")
		{
			auto text = WidgetFactory::CreateWidget<Text>();
			text->Deserialize(it);
			AddChild(text);
		}
		else if (strType == "Button")
		{
			auto button = WidgetFactory::CreateWidget<Button>();
			button->Deserialize(it);
			AddChild(button);
		}
	}
}
