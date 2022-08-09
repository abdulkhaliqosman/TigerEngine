#include "wolfnetworking/wolfpch.h"
#include "wolfnetworking/windows/winnetworksystem.h"

#include <jaguarcore/thread/jobsystem.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"

namespace wolf
{
	WinNetworkSystem::WinNetworkSystem(jgr::iEngine& iEngine)
		:iNetworkSystem(iEngine), m_ServerJob(this->m_Server), m_ClientJob(this->m_Client)
	{
		m_MsgHandler.SetNetworkSystem(this);
	}

	void WinNetworkSystem::Setup()
	{
		WSADATA wsaData;
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			printf("WSAStartup failed: %d\n", iResult);
		}

		m_Server.RegisterOnReceive(
			[this](const NetClientData& src, const char* msg, int len)
			{
				m_MsgHandler.OnReceivePacket(src, msg, len);
			}
		);

		m_Client.RegisterOnReceive(
			[this](const NetClientData& src, const char* msg, int len)
			{
				m_MsgHandler.OnReceivePacket(src, msg, len);
			}
		);
	}

	void WinNetworkSystem::Teardown()
	{
		switch (m_NetworkType)
		{
		case NetworkType::Client:
		{
			m_Client.Disconnect();
			break;
		}
		case NetworkType::Server:
		{
			m_Server.Disconnect();
			break;
		}
		}
	}

	void WinNetworkSystem::StartScene()
	{

	}

	void WinNetworkSystem::StopScene()
	{

	}

	void WinNetworkSystem::Update()
	{
		switch (m_NetworkType)
		{
		case NetworkType::Client:
		{
			GetJobSystem().PushJob(&m_ClientJob);
			break;
		}
		case NetworkType::Server:
		{
			GetJobSystem().PushJob(&m_ServerJob);
			break;
		}
		}

	}
	void WinNetworkSystem::StartClient(const std::string& address)
	{
		assert(m_NetworkType == NetworkType::Disabled);

		if (m_Client.CreateSocket(address, DEFAULT_PORT))
		{
			m_NetworkType = NetworkType::Client;

		}

	}

	void WinNetworkSystem::StartServer()
	{
		assert(m_NetworkType == NetworkType::Disabled);

		if (m_Server.CreateSocket(DEFAULT_PORT))
		{
			m_NetworkType = NetworkType::Server;

		}

	}

	void WinNetworkSystem::Disconnect()
	{
		switch (m_NetworkType)
		{
		case NetworkType::Client:
		{
			m_Client.Disconnect();
			break;
		}
		case NetworkType::Server:
		{
			m_Server.Disconnect();
			break;
		}
		}

		m_NetworkType = NetworkType::Disabled;
	}

	NetworkType WinNetworkSystem::GetCurrentNetworkType() const
	{
		return m_NetworkType;
	}

	std::string WinNetworkSystem::IpIntToString(IpAddress ip) const
	{
		in_addr in;
		in.s_addr = ip;

		char buffer[INET_ADDRSTRLEN];

		return inet_ntop(AF_INET, &in, buffer, sizeof(buffer));
	}

	IpAddress WinNetworkSystem::NetUserIdToIpInt(NetUserId id) const
	{
		switch (m_NetworkType)
		{
		case NetworkType::Client:
		{
			// we cannot get ip of other clients since we're strictly client-server. only interact with other clients with id
			return m_Client.GetClientData().ipAddress; 
			break;
		}
		case NetworkType::Server:
		{
			std::vector<const NetClientData*> clientsdata = m_Server.GetClientsData();
			for (const NetClientData* client : clientsdata)
			{
				if (id == client->userId)
				{
					return client->ipAddress;
				}
			}
			break;
		}
		}
		return 0;
	}
}