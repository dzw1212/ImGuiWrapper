#pragma once
#include <xhash>
#include "Base/Json.h"

class UUID
{
public:
	UUID();
	UUID(uint64_t Id);
	UUID(const UUID&) = default;

	operator uint64_t() const { return m_u64Id; }

public:
	uint64_t m_u64Id;
};

namespace std
{
	template<>
	struct std::hash<UUID>
	{
		std::size_t operator()(const UUID& uuid) const
		{
			return std::hash<uint64_t>()((uint64_t)uuid);
		}
	};
}

namespace nlohmann
{
	static void to_json(json& data, const UUID& id)
	{
		data = json{
			{"id", id.m_u64Id}
		};
	}
	static void from_json(const json& data, UUID& id)
	{
		data.at("id").get_to(id.m_u64Id);
	}
}