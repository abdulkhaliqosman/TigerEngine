#pragma once

#include "wolfnetworking/system/inetworkserver.h"

namespace tgr
{
	class GameNetworkSystem;

	class GameNetworkServer : public wolf::iServerListener
	{
	public:
		virtual void OnServerStart(const wolf::iNetworkServer& server) override;
		virtual void OnServerStop(const wolf::iNetworkServer& server) override;
		virtual void OnClientConnected(const wolf::iNetworkServer& server, const wolf::NetClientData& client) override;

		void SetSystem(GameNetworkSystem* value) { m_System = value; }

	private:
		GameNetworkSystem* m_System = nullptr;
	};
}