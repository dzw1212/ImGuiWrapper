#include "UUID.h"

#include <random>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_RandomEngine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

UUID::UUID()
	: m_u64Id(s_UniformDistribution(s_RandomEngine))
{
}
UUID::UUID(uint64_t Id)
	: m_u64Id(Id)
{
}
