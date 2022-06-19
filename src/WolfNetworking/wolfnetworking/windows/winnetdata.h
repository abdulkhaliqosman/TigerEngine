#pragma once

#include "wolfnetworking/system/netdata.h"
#include <winsock2.h>

namespace wolf
{
	struct WinNetServerData : public NetServerData
	{
		SOCKET socket;
	};

	struct WinNetClientData : public NetClientData
	{
		SOCKET socket;
	};
}