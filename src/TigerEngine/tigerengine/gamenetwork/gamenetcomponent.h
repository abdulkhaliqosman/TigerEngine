#pragma once

#include "wolfnetworking/component/netcomponent.h"

namespace tgr
{
	class GameNetworkSystem;

	class GameNetComponent : public wolf::NetComponent
	{
	public:
		inline void SetGameNetwork(GameNetworkSystem* value) { m_GameNetwork = value; }
		inline GameNetworkSystem* GetGameNetwork() { return m_GameNetwork; }

	private:
		GameNetworkSystem* m_GameNetwork = nullptr;
	};
}