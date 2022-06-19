#pragma once

#include <string>

#include <jaguarcore/thread/jobsystem.h>
#include "wolfnetworking/system/inetworkserver.h"
#include "wolfnetworking/windows/winnetdata.h"

namespace wolf
{
	class WinServer : public iNetworkServer
	{
		
	public:
		bool CreateSocket(const std::string& port);
		void Disconnect();

		void Update();

		void Send(NetUserId dest, const char* buffer, int length) override;
		void Broadcast(const char* buffer, int length) override;

		inline void RegisterOnReceive(const OnReceiveFunc& func) override { m_OnReceiveFuncs.push_back(func); }

		std::vector<const NetClientData*> GetClientsData() const override;
		inline const NetServerData& GetServerData() const override { return m_ServerData; }
		void AddListener(iServerListener* listener) override { m_ServerListeners.push_back(listener); }
		// TODO: Unregister
		
		void SelectSocket();
		void ReceiveSockets();

	private:
		void AcceptSocket();
		void SendSockets();

		WinNetServerData m_ServerData;

		NetUserId m_NextUserId = 0; // just a counter that keeps incrementing

		std::vector<WinNetClientData> m_ClientData;
		std::vector<OnReceiveFunc> m_OnReceiveFuncs;
		std::vector<iServerListener*> m_ServerListeners;
	};

	class WinServerJob : public jgr::Job
	{
	public:
		WinServerJob(WinServer& winServer) : m_Server(winServer) {}

		void Execute() override;

	private:
		WinServer& m_Server;
	};
}