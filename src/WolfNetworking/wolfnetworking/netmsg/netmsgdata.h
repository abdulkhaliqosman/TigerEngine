#pragma once

#include <functional>

namespace wolf
{
	union NetMsgTypeId
	{
		char u8 [8];
		unsigned long long u64;
	};

	inline bool operator==(const NetMsgTypeId& lhs, const NetMsgTypeId& rhs)
	{
		return (lhs.u64 == rhs.u64);
	}
}

template<>
struct std::hash<wolf::NetMsgTypeId>
{
	inline std::size_t operator()(const wolf::NetMsgTypeId& val) const
	{
		return std::hash<unsigned long long>{}(val.u64);
	}
};