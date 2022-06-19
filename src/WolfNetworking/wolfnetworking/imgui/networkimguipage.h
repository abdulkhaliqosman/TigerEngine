#pragma once

#include <jaguarcore/imgui/imguipage.h>

#include <wolfnetworking/netmsg/netmsg.h>
#include <vector>
#include <string>

namespace wolf
{
	class iNetworkSystem;

	class TestNetMsg : public NetMsg<TestNetMsg>
	{
	public:
		using super = NetMsg<TestNetMsg>;

		void Serialize(NetMsgWriteVisitor& visitor) const override;
		void Deserialize(const NetMsgReadVisitor& visitor) override;

		int GetPacketSize() const override;

		void SetTestMessage(const std::string& msg) { m_Message = msg; }
		const std::string& GetTestMessage() const { return m_Message; }

		static constexpr NetMsgTypeId s_NetMsgTypeId{ "DBGTEST" };
	private:

		std::string m_Message;
	};

	class NetworkImguiPage : public jgr::ImguiPage
	{
	public:
		void Startup() override;
		void Update() override;

		inline const char* GetMenuName() override { return "Network"; }
		inline const char* GetMenuItemName() override { return "Network"; }

		void SetNetworkSystem(iNetworkSystem* value) { m_NetworkSystem = value; }
	private:
		void DisplayChat();

		void OnReceive(const TestNetMsg& src);

		iNetworkSystem* m_NetworkSystem;

		std::vector<std::string> m_Chatlog;
	};
}