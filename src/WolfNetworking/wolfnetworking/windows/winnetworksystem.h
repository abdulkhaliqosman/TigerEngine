#pragma once

#include "wolfnetworking/system/inetworksystem.h"

#include "wolfnetworking/windows/winclient.h"
#include "wolfnetworking/windows/winserver.h"
#include <wolfnetworking/netmsg/netmsghandler.h>

namespace wolf
{
	class WinNetworkSystem : public iNetworkSystem
	{
	public:
		WinNetworkSystem(jgr::iEngine& iEngine);
		inline virtual ~WinNetworkSystem() {}

		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;

		void StartClient(const std::string& address) override;
		void StartServer() override;

		void Disconnect() override;
		
		inline iNetworkClient* GetClient() override { return &m_Client; }
		inline iNetworkServer* GetServer() override { return &m_Server; }

		NetworkType GetCurrentNetworkType() const override;

		std::string IpIntToString(IpAddress) const override;
		IpAddress NetUserIdToIpInt(NetUserId) const override;
		inline NetMsgHandler& GetMsgHandler() override { return m_MsgHandler; }
	private:

		WinServerJob m_ServerJob;
		WinClientJob m_ClientJob;

		NetworkType m_NetworkType = NetworkType::Disabled;

		WinServer m_Server;
		WinClient m_Client;

		NetMsgHandler m_MsgHandler;
	};
}