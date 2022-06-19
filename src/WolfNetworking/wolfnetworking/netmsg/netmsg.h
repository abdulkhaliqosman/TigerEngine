#pragma once

#include "wolfnetworking/system/netdata.h"
#include "wolfnetworking/netmsg/netmsgdata.h"
#include "wolfnetworking/netvisitor/netvisitor.h"

namespace wolf
{
	class iNetMsg
	{
	public:
		virtual void Serialize(NetMsgWriteVisitor& visitor) const = 0;
		virtual void Deserialize(const NetMsgReadVisitor& visitor) = 0;

		virtual const NetMsgTypeId& GetNetMsgTypeId() const = 0;
		virtual int GetPacketSize() const = 0;

		struct NetMsgHeader
		{
			NetMsgTypeId msgTypeId;

			int packetSize;
			NetUserId destinationId = -1;
			NetUserId sourceId = -1;
		};

		void SetNetMsgHeader(const NetMsgHeader& val) { m_NetMsgHeader = val; }

		NetMsgHeader& GetNetMsgHeader() { return m_NetMsgHeader; }
		const NetMsgHeader& GetNetMsgHeader() const { return m_NetMsgHeader; }

	private:
		NetMsgHeader m_NetMsgHeader;
	};

	template <typename T>
	class NetMsg : public iNetMsg
	{
	public:
		using super = iNetMsg;

		static NetMsg<T>* CreateNetMsg() { return jgr::New<T>(); }
		const NetMsgTypeId& GetNetMsgTypeId() const override { return T::s_NetMsgTypeId; }

		void Serialize(NetMsgWriteVisitor& visitor) const override;
		void Deserialize(const NetMsgReadVisitor& visitor) override;

		int GetPacketSize() const override;

		
	};

	template <typename T>
	void NetMsg<T>::Serialize(NetMsgWriteVisitor& visitor) const
	{
		visitor.Write(GetNetMsgHeader().msgTypeId.u64);
		visitor.Write(GetNetMsgHeader().destinationId);
		visitor.Write(GetNetMsgHeader().sourceId);
		visitor.Write(GetNetMsgHeader().packetSize);
	}

	template <typename T>
	void NetMsg<T>::Deserialize(const NetMsgReadVisitor& visitor)
	{
		visitor.Read(GetNetMsgHeader().msgTypeId.u64);
		visitor.Read(GetNetMsgHeader().destinationId);
		visitor.Read(GetNetMsgHeader().sourceId);
		visitor.Read(GetNetMsgHeader().packetSize);
	}

	template <typename T>
	int NetMsg<T>::GetPacketSize() const
	{
		return sizeof(GetNetMsgHeader().msgTypeId.u64)
			+ sizeof(GetNetMsgHeader().destinationId)
			+ sizeof(GetNetMsgHeader().sourceId)
			+ sizeof(GetNetMsgHeader().packetSize);
	}
}