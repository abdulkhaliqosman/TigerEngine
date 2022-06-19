#include "wolfnetworking/wolfpch.h"
#include <wolfnetworking/netmsg/netmsghandler.h>
#include "wolfnetworking/system/inetworksystem.h"
#include "wolfnetworking/system/inetworkclient.h"
#include "wolfnetworking/system/inetworkserver.h"

namespace wolf
{
	void NetMsgHandler::InitNetMsgHeader(iNetMsg& msg)
	{
		iNetMsg::NetMsgHeader header;
		header.msgTypeId = msg.GetNetMsgTypeId();
		header.packetSize = msg.GetPacketSize();
		msg.SetNetMsgHeader(header);

		// the other 2 header variables will be supplied by the sender function
	}

	void NetMsgHandler::OnReceivePacket(const NetClientData&, const char* data, int length)
	{
		if (data == nullptr)
		{
			return;
		}

		if (length < sizeof(iNetMsg::NetMsgHeader))
		{
			return;
		}
		
		NetMsgReadVisitor visitor(data, length);

		NetMsgTypeId id {0};

		visitor.Peek(id.u64);

		auto iter = m_NetMsgMap.find(id);
		if (iter != m_NetMsgMap.end())
		{
			iter->second->CreateReceivedNetMsg(visitor);
		}
	}

	void NetMsgHandler::SendNetMsgToServer(iNetMsg& msg)
	{
		InitNetMsgHeader(msg);

		char buffer[1024]{ 0 };
		NetMsgWriteVisitor visitor(buffer, 1024);
		msg.Serialize(visitor);

		m_NetworkSystem->GetClient()->Send(buffer, visitor.GetWrittenLength());
	}

	void NetMsgHandler::SendNetMsgToClient(NetUserId destId, iNetMsg& msg)
	{
		InitNetMsgHeader(msg);
		msg.GetNetMsgHeader().destinationId = destId;
		
		char buffer[1024]{ 0 };
		NetMsgWriteVisitor visitor(buffer, 1024);
		msg.Serialize(visitor);
		m_NetworkSystem->GetServer()->Send(destId, buffer, visitor.GetWrittenLength());
	}

	void NetMsgHandler::BroadcastNetMsgToClients(iNetMsg& msg)
	{
		InitNetMsgHeader(msg);

		char buffer[1024]{ 0 };
		NetMsgWriteVisitor visitor(buffer, 1024);
		msg.Serialize(visitor);

		m_NetworkSystem->GetServer()->Broadcast(buffer, visitor.GetWrittenLength());
	}
}
