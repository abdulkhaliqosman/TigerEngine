#include "tigerengine/tigerpch.h"
#include "tigerengine/gamenetwork/gamenetworkserver.h"
#include "tigerengine/gamenetwork/gamenetmsg.h"
#include "tigerengine/gamenetwork/gamenetworksystem.h"
#include "wolfnetworking/system/inetworksystem.h"
#include <wolfnetworking/netmsg/netmsghandler.h>

namespace tgr
{
	void GameNetworkServer::OnServerStart(const wolf::iNetworkServer& server)
	{
		

	}

	void GameNetworkServer::OnServerStop(const wolf::iNetworkServer& server)
	{

	}

	void GameNetworkServer::OnClientConnected(const wolf::iNetworkServer& server, const wolf::NetClientData& client)
	{
		JoinSessionNetMsg msg;

		msg.SetPlayerId(client.userId); // for now they are synced to the same id

		m_System->GetNetworkSystem()->GetMsgHandler().SendNetMsgToClient(client.userId, msg);
		// send peer joined for everyone else
	}
}