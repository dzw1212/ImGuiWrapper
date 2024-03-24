#include "Button.h"

#include "imgui.h"

#include "Base/Log.h"

void Button::Draw()
{
	ImGui::Button(m_strContent.c_str());
	if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
	{
		if (m_mapClickFunc[eButtonMouse_Left])
			m_mapClickFunc[eButtonMouse_Left]();
	}
	else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
	{
		if (m_mapClickFunc[eButtonMouse_Right])
			m_mapClickFunc[eButtonMouse_Right]();
	}
	else if (ImGui::IsItemClicked(ImGuiMouseButton_Middle))
	{
		if (m_mapClickFunc[eButtonMouse_Middle])
			m_mapClickFunc[eButtonMouse_Middle]();
	}
}

void Button::Serialize(Json& data)
{
	data = {
		{"type", GetTypeName()},
		{"context", m_strContent},

		{"uuid", m_ID},
	};
}

void Button::Deserialize(const Json& data)
{
	data.at("context").get_to(m_strContent);

	data.at("uuid").get_to(m_ID);
}

void Button::SetClickFunc(std::function<void(void)> func, eButtonMouse_ button)
{
	m_mapClickFunc[button] = func;
}
