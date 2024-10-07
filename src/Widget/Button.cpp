#include "Button.h"

#include "imgui.h"

#include "Base/Log.h"

void Button::Draw()
{
	if (m_Layout.bValid)
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 anchorPos = ImVec2(windowSize.x * m_Layout.Pivot.x, windowSize.y * m_Layout.Pivot.y);

		ImVec2 textSize = ImGui::CalcTextSize(m_strContent.c_str());
		const auto& style = ImGui::GetStyle();
		float fWidth = textSize.x + style.FramePadding.x * 2.0f;
		float fHeight = textSize.y + style.FramePadding.y * 2.0f;
		ImVec2 pivotPos = ImVec2(fWidth * m_Layout.Pivot.x, fWidth * m_Layout.Pivot.y);

		ImVec2 calcPos = ImVec2(anchorPos.x - pivotPos.x + m_Layout.Pos.x, anchorPos.y - pivotPos.y + m_Layout.Pos.y);

		ImGui::SetCursorPos(calcPos);
	}

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
