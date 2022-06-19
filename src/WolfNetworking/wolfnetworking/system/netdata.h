#pragma once

#include <functional>

namespace wolf
{

	using NetUserId = int;
	using IpAddress = unsigned int;

	constexpr NetUserId NET_USER_INVALID_ID = -1;
	constexpr NetUserId NET_USER_SERVER_ID = 0;

	struct NetClientData
	{
		NetUserId userId;
		IpAddress ipAddress;
	};

	struct NetServerData
	{
		IpAddress ipAddress;
	};

	using OnReceiveFunc = std::function<void(const NetClientData&, const char* msg, int len)>;
}