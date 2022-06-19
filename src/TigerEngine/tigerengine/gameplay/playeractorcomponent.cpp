#include <tigerengine/tigerpch.h>

#include <tigerengine/gameplay/playeractorcomponent.h>
#include "wolfnetworking/system/inetworksystem.h"
#include <wolfnetworking/netmsg/netmsghandler.h>
#include "tigerengine/gamenetwork/gamenetworksystem.h"

namespace tgr
{
	void PlayerActorComponent::Startup()
	{
		m_Timer = 0.0f;
	}

	void PlayerActorComponent::Update()
	{
		if (GetGameNetwork()->GetIsInSession() == false)
		{
			return;
		}

		if (m_UserId == GetGameNetwork()->GetLocalPlayerId())
		{
			// get input

			bool moved = false;



			if (moved)
			{
				MovePlayerNetMsg msg;
				msg.SetPlayerId(m_UserId);
				msg.SetPlayerPosition(GetTransform()->GetLocalPosition());
				GetNetwork()->GetMsgHandler().SendNetMsgToServer(msg);
			}
		}
	}

	void PlayerActorComponent::Shutdown()
	{

	}

	void PlayerActorComponent::OnReceive(const MovePlayerNetMsg& msg)
	{
		if (msg.GetPlayerId() == m_UserId)
		{
			GetTransform()->SetLocalPosition(msg.GetPlayerPosition());
		}

		if (GetGameNetwork()->GetIsServer())
		{
			// broadcast to all clients
			MovePlayerNetMsg copy = msg;
			GetNetwork()->GetMsgHandler().BroadcastNetMsgToClients(copy);
		}
	}

	void MovePlayerNetMsg::Serialize(NetMsgWriteVisitor& visitor) const
	{
		super::Serialize(visitor);
		visitor.Write(m_PlayerId);
		visitor.Write(m_PlayerPosition.x());
		visitor.Write(m_PlayerPosition.y());
		visitor.Write(m_PlayerPosition.z());
	}

	void MovePlayerNetMsg::Deserialize(const NetMsgReadVisitor& visitor)
	{
		super::Deserialize(visitor);
		visitor.Read(m_PlayerId);
		visitor.Read(m_PlayerPosition.x());
		visitor.Read(m_PlayerPosition.y());
		visitor.Read(m_PlayerPosition.z());
	}

	int MovePlayerNetMsg::GetPacketSize() const
	{
		int superSize = super::GetPacketSize();
		int playerPositionSize = sizeof(float) * 3;
		int playerIdSize = sizeof(int);

		return superSize + playerPositionSize + playerIdSize;
	}
}