#include "Text.h"
#include "Base/Log.h"
#include "imgui.h"

void Text::Draw()
{

	switch (m_Flags)
	{
	case eTextFlags_None:
		ImGui::Text(m_strContent.c_str());
		break;
	case eTextFlags_Color:
		ImGui::TextColored({ m_Color.fRed, m_Color.fGreen, m_Color.fBlue, 1.f}, m_strContent.c_str());
		break;
	case eTextFlags_Label:
		ImGui::LabelText(std::format("##{}", m_ID.m_u64Id).c_str(), m_strContent.c_str());
		break;
	case eTextFlags_Bulletin:
		ImGui::BulletText(m_strContent.c_str());
		break;
	case eTextFlags_Unformatted:
		ImGui::TextUnformatted(m_strContent.c_str());
		break;
	case eTextFlags_Disable:
		ImGui::TextDisabled(m_strContent.c_str());
		break;
	case eTextFlags_Wrapped:
		ImGui::TextWrapped(m_strContent.c_str());
		break;
	case eTextFlags_Separator:
		ImGui::SeparatorText(m_strContent.c_str());
		break;
	default:
		Log::Error("flags {} not find", (int)m_Flags);
		break;
	}
}

void Text::Serialize(Json& data)
{
	data = Json{
		{"type", GetTypeName()},
		{"context", m_strContent},
		{"color", m_Color},
		{"flags", m_Flags},
		{"uuid", m_ID},
	};
}

void Text::Deserialize(const Json& data)
{
	data.at("context").get_to(m_strContent);
	data.at("color").get_to(m_Color);
	data.at("flags").get_to(m_Flags);
	data.at("uuid").get_to(m_ID);
}
