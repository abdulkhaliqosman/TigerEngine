#pragma once

#include <jaguarcore\system\isystem.h>
#include <vector>
#include "tigerengine/gamenetwork/gamenetworkserver.h"
#include "wolfnetworking/system/inetworksystem.h"

namespace tgr
{
	class JoinSessionNetMsg;
	class PeerJoinSessionNetMsg;

	using NetPlayerId = int;

	class GameNetworkSystem : jgr::iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline int GetLocalPlayerId() const { return m_LocalPlayerId; }
		inline const std::vector<int>& GetAvailablePeerIds() const { return m_PeerPlayerIds; }

		inline void SetNetworkSystem(wolf::iNetworkSystem* value) { m_NetworkSystem = value; }
		inline wolf::iNetworkSystem* GetNetworkSystem() { return m_NetworkSystem; }
		inline bool GetIsInSession() const { return m_IsInSession; }
		inline bool GetIsServer() const { return m_NetworkSystem->GetCurrentNetworkType() == wolf::NetworkType::Server; }
		inline bool GetIsClient() const { return m_NetworkSystem->GetCurrentNetworkType() == wolf::NetworkType::Client; }

	private:
		void OnJoinSession(const JoinSessionNetMsg& msg);
		void OnPeerJoinSession(const PeerJoinSessionNetMsg& msg);

	private:
		bool m_IsInSession = false;

		GameNetworkServer m_GameServerListener;
		wolf::iNetworkSystem* m_NetworkSystem = nullptr;

		NetPlayerId m_LocalPlayerId = 0;

		std::vector<NetPlayerId> m_PeerPlayerIds;
	};
}