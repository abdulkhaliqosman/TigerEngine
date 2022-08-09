#pragma once

#include <jaguarcore\engine\ienginesystem.h>
#include <string>
#include "wolfnetworking/system/netdata.h"

namespace wolf
{
	enum class NetworkType
	{
		Disabled,
		Client,
		Server
	};

	class iNetworkServer;
	class iNetworkClient;
	class NetMsgHandler;

	class iNetworkSystem : public jgr::iEngineSystem
	{
	public:
		inline iNetworkSystem(jgr::iEngine& iEngine) : jgr::iEngineSystem(iEngine){}
		virtual void StartClient(const std::string& address) = 0;
		virtual void StartServer() = 0;
		virtual void Disconnect() = 0;

		virtual iNetworkClient* GetClient() = 0;
		virtual iNetworkServer* GetServer() = 0;

		virtual NetworkType GetCurrentNetworkType() const = 0;

		virtual std::string IpIntToString(IpAddress) const = 0;
		virtual IpAddress NetUserIdToIpInt(NetUserId) const = 0;

		inline std::string NetUserIdToString(NetUserId id) { return IpIntToString(NetUserIdToIpInt(id)); }

		virtual NetMsgHandler& GetMsgHandler() = 0;


	};
}