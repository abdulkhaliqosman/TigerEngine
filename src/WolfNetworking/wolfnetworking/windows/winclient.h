#pragma once

#include <string>

#include "wolfnetworking/windows/winnetdata.h"
#include "wolfnetworking/system/inetworkclient.h"
#include <jaguarcore/thread/jobsystem.h>

namespace wolf
{
	class WinClient : public iNetworkClient
	{
	public:
		bool CreateSocket(const std::string& address, const std::string& port);
		void Disconnect();

		void Update();

		void Send(const char* buffer, int length) override;
		inline void RegisterOnReceive(const OnReceiveFunc& func) override { m_OnReceiveFuncs.push_back(func); }

		inline const NetClientData& GetClientData() const override { return m_ClientData; }

		void Receive();
	private:

		WinNetClientData m_ClientData;
		std::vector<OnReceiveFunc> m_OnReceiveFuncs;
	};

	class WinClientJob : public jgr::Job
	{
	public:
		WinClientJob(WinClient& winClient) : m_Client(winClient) {}

		void Execute() override;

	private:
		WinClient& m_Client;
	};

}