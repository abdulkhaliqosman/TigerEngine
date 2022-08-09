#include "tigerengine/tigerpch.h"
#include "tigerengine/gamenetwork/gamenetworksystem.h"

#include "tigerengine/gamenetwork/gamenetmsg.h"
#include "wolfnetworking/system/inetworksystem.h"
#include <wolfnetworking/netmsg/netmsghandler.h>

namespace tgr
{
	void GameNetworkSystem::Setup()
	{
		std::function<void(const JoinSessionNetMsg&)> joinfunc
			= [this](const JoinSessionNetMsg& msg)
		{
			OnJoinSession(msg);
		};

		m_NetworkSystem->GetMsgHandler().RegisterNetMsgType(joinfunc);

		std::function<void(const PeerJoinSessionNetMsg&)> peerjoinfunc
			= [this](const PeerJoinSessionNetMsg& msg)
		{
			OnPeerJoinSession(msg);
		};

		m_NetworkSystem->GetMsgHandler().RegisterNetMsgType(peerjoinfunc);
		m_NetworkSystem->GetServer()->AddListener(&m_GameServerListener);
		m_GameServerListener.SetSystem(this);
	}

	void GameNetworkSystem::Teardown()
	{

	}

	void GameNetworkSystem::StartScene()
	{

	}

	void GameNetworkSystem::StopScene()
	{

	}

	void GameNetworkSystem::Update()
	{

	}

	void GameNetworkSystem::OnJoinSession(const JoinSessionNetMsg& msg)
	{
		m_LocalPlayerId = msg.GetPlayerId();
		m_IsInSession = true;
	}

	void GameNetworkSystem::OnPeerJoinSession(const PeerJoinSessionNetMsg& msg)
	{
		m_PeerPlayerIds.push_back(msg.GetPlayerId());
	}
}
