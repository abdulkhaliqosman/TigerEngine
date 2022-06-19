#pragma once

#include <wolfnetworking/netmsg/netmsg.h>

namespace tgr
{
	class JoinSessionNetMsg : public wolf::NetMsg<JoinSessionNetMsg>
	{
	public:
		using super = wolf::NetMsg<JoinSessionNetMsg>;

		void Serialize(NetMsgWriteVisitor& visitor) const override;
		void Deserialize(const NetMsgReadVisitor& visitor) override;
		int GetPacketSize() const override;

		inline int GetPlayerId() const { return m_Data.localPlayerId; }
		inline void SetPlayerId(int value) { m_Data.localPlayerId = value; }
		
		inline const std::vector<int>& GetJoinedPeers() const { return m_Data.joinedPeersPlayerId; }
		inline void SetJoinedPeers(const std::vector<int>& value) { m_Data.joinedPeersPlayerId = value; }

		static constexpr wolf::NetMsgTypeId s_NetMsgTypeId{ "JOINSSN" };

	private:
		struct JoinSessionNetMsgData
		{
			int localPlayerId;
			std::vector<int> joinedPeersPlayerId;
		};

		JoinSessionNetMsgData m_Data;
	};

	class PeerJoinSessionNetMsg : wolf::NetMsg<PeerJoinSessionNetMsg>
	{
	public:
		using super = wolf::NetMsg<PeerJoinSessionNetMsg>;

		void Serialize(NetMsgWriteVisitor& visitor) const override;
		void Deserialize(const NetMsgReadVisitor& visitor) override;
		int GetPacketSize() const override;

		inline int GetPlayerId() const { return m_Data.peerPlayerId; }
		static constexpr wolf::NetMsgTypeId s_NetMsgTypeId{ "PJOINSN" };

	private:
		struct PeerJoinSessionNetMsgData
		{
			int peerPlayerId;
		};

		PeerJoinSessionNetMsgData m_Data;
	};
}
