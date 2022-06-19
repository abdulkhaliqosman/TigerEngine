#pragma once

#include "wolfnetworking/system/netdata.h"

#include <vector>

namespace wolf
{
	class iServerListener;

	class iNetworkServer
	{
	public:
		virtual void RegisterOnReceive(const OnReceiveFunc& func) = 0;

		virtual void Send(NetUserId dest, const char* buffer, int length) = 0;
		virtual void Broadcast(const char* buffer, int length) = 0;

		virtual std::vector<const NetClientData*> GetClientsData() const = 0;
		virtual const NetServerData& GetServerData() const = 0;

		virtual void AddListener(iServerListener* listener) = 0;
	};

	class iServerListener
	{
	public:
		virtual void OnServerStart(const iNetworkServer& server) = 0;
		virtual void OnServerStop(const iNetworkServer& server) = 0;
		virtual void OnClientConnected(const iNetworkServer& server, const NetClientData& client) = 0;
		// TODO: write disconnected code
	};
}