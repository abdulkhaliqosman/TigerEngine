#pragma once

#include <wolfnetworking/netmsg/netmsg.h>
#include "tigerengine/gamenetwork/gamenetcomponent.h"

namespace tgr
{
	class MovePlayerNetMsg;

	class PlayerActorComponent : public GameNetComponent
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void OnReceive(const MovePlayerNetMsg& msg);

		inline int GetUserId() { return m_UserId; }
		inline void SetUserId(int userId) { m_UserId = userId; }

	private:
		int m_UserId = 0;
		float m_Timer = 0.0f;
	};

	class MovePlayerNetMsg : public wolf::NetMsg<MovePlayerNetMsg>
	{
	public:
		using super = NetMsg<MovePlayerNetMsg>;

		void Serialize(NetMsgWriteVisitor& visitor) const override;
		void Deserialize(const NetMsgReadVisitor& visitor) override;

		int GetPacketSize() const override;

		vec3 GetPlayerPosition() const { return m_PlayerPosition; }
		void SetPlayerPosition(const vec3& pos) { m_PlayerPosition = pos; }

		int GetPlayerId() const { return m_PlayerId; }
		void SetPlayerId(int id) { m_PlayerId = id; }

		static constexpr wolf::NetMsgTypeId s_NetMsgTypeId{ "MOVPLYR" };
	private:

		vec3 m_PlayerPosition;
		int m_PlayerId;
	};
}