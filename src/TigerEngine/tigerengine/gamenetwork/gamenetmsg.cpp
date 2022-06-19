#include "tigerengine/tigerpch.h"
#include "tigerengine/gamenetwork/gamenetmsg.h"

namespace tgr
{
	void JoinSessionNetMsg::Serialize(NetMsgWriteVisitor& visitor) const
	{
		super::Serialize(visitor);
		visitor.Write(m_Data.localPlayerId);
	}

	void JoinSessionNetMsg::Deserialize(const NetMsgReadVisitor& visitor)
	{
		super::Deserialize(visitor);
		visitor.Read(m_Data.localPlayerId);
	}

	int JoinSessionNetMsg::GetPacketSize() const
	{
		int superSize = super::GetPacketSize();
		int playerIdSize = sizeof(int);
		return superSize + playerIdSize;
	}

	void PeerJoinSessionNetMsg::Serialize(NetMsgWriteVisitor& visitor) const
	{
		super::Serialize(visitor);
		visitor.Write(m_Data.peerPlayerId);
	}

	void PeerJoinSessionNetMsg::Deserialize(const NetMsgReadVisitor& visitor)
	{
		super::Deserialize(visitor);
		visitor.Read(m_Data.peerPlayerId);

	}

	int PeerJoinSessionNetMsg::GetPacketSize() const
	{
		int superSize = super::GetPacketSize();
		int playerIdSize = sizeof(int);
		return superSize + playerIdSize;
	}
}