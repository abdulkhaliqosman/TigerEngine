#pragma once

#include "wolfnetworking/system/netdata.h"

#include <vector>

namespace wolf
{
	class iNetworkClient
	{
	public:
		virtual void RegisterOnReceive(const OnReceiveFunc& func) = 0;

		virtual void Send(const char* buffer, int length) = 0;

		virtual const NetClientData& GetClientData() const = 0;
	};
}