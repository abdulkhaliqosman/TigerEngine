#include "wolfnetworking/wolfpch.h"
#include "wolfnetworking/windows/winserver.h"

#include <ws2tcpip.h>
#include "optick.h"

namespace wolf
{
	void WinServerJob::Execute()
	{
		// lazy version first, 1 thread execute
		m_Server.SelectSocket();
		m_Server.ReceiveSockets();
	}

	bool WinServer::CreateSocket(const std::string& port)
	{
		struct addrinfo* result = NULL, * ptr = NULL, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		int iResult;
		// Resolve the local address and port to be used by the server
		iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return false;
		}

		SOCKET listenSocket = INVALID_SOCKET;

		// Create a SOCKET for the server to listen for client connections
		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (listenSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}

		// Setup the TCP listening socket
		iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return false;
		}


		freeaddrinfo(result);

		if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			printf("Listen failed with error: %ld\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return false;
		}

		sockaddr_in sockname;
		int sz = sizeof(sockname);
		getsockname(listenSocket, reinterpret_cast<sockaddr*>(&sockname), &sz);
		m_ServerData.ipAddress = sockname.sin_addr.s_addr;
		m_ServerData.socket = listenSocket;
		
		for (auto* iter : m_ServerListeners)
		{
			iter->OnServerStart(*this);
		}

		return true;
	}

	void WinServer::Disconnect()
	{
		for (WinNetClientData& data : m_ClientData)
		{
			SOCKET socket = data.socket;

			int iResult;
			iResult = shutdown(socket, SD_SEND);
			if (iResult == SOCKET_ERROR)
			{
				printf("shutdown failed: %d\n", WSAGetLastError());
				closesocket(socket);
				WSACleanup();
			}
		}

		m_ClientData.clear();

		closesocket(m_ServerData.socket);

		for (auto* iter : m_ServerListeners)
		{
			iter->OnServerStop(*this);
		}
	}

	void WinServer::Update()
	{
		
	}

	void WinServer::Send(NetUserId dest, const char* buffer, int length)
	{
		for (const WinNetClientData& client : m_ClientData)
		{
			if (dest == client.userId)
			{
				send(client.socket, buffer, length, 0);
				return;
			}
		}
	}

	void WinServer::Broadcast(const char* buffer, int length)
	{
		for (const WinNetClientData& client : m_ClientData)
		{
			send(client.socket, buffer, length, 0);
		}
	}

	std::vector<const NetClientData*> WinServer::GetClientsData() const
	{
		std::vector<const NetClientData*> result;

		for (const WinNetClientData& data : m_ClientData)
		{
			result.push_back(&data);
		}

		return result;
	}

	void WinServer::SelectSocket()
	{
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 1000; // don't block too long, only 1 ms

		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(m_ServerData.socket, &readset);

		// as a start we accept a socket once a frame only
		int maxfdp1 = m_ServerData.socket + 1;
		int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
		if(readyfd == SOCKET_ERROR)
		{
			printf("select failed: %d\n", WSAGetLastError());
			return;
		}

		if (readyfd == 0)
		{
			// no fd just early out
			return;
		}

		if (FD_ISSET(m_ServerData.socket, &readset))
		{
			AcceptSocket();
		}
	}

	void WinServer::AcceptSocket()
	{
		OPTICK_EVENT();
		// Accept Connection
		SOCKET clientSocket;
		clientSocket = INVALID_SOCKET;

		sockaddr addr;
		int size = sizeof(addr);
		ZeroMemory(&addr, size);

		// Accept a client socket
		clientSocket = accept(m_ServerData.socket, &addr, &size);
		if (clientSocket == INVALID_SOCKET)
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(m_ServerData.socket);
			WSACleanup();
			return;
		}

		WinNetClientData client;
		client.userId = ++m_NextUserId;
		client.socket = clientSocket;

		if (addr.sa_family == AF_INET)
		{
			const sockaddr_in* addrin = reinterpret_cast<sockaddr_in*>(&addr);
			client.ipAddress = addrin->sin_addr.s_addr;
		}

		m_ClientData.push_back(client);

		for (auto* iter : m_ServerListeners)
		{
			iter->OnClientConnected(*this, client);
		}
	}

	void WinServer::ReceiveSockets()
	{
		// as a start we recv once per socket a frame only
		for (WinNetClientData& data : m_ClientData)
		{
			timeval timeout;
			timeout.tv_usec = 0;
			timeout.tv_usec = 100; // don't block too long, only 0.1 ms

			fd_set readset;
			FD_ZERO(&readset);
			FD_SET(data.socket, &readset);

			// as a start we accept a socket once a frame only
			int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
			if (readyfd == SOCKET_ERROR)
			{
				printf("select failed: %d\n", WSAGetLastError());
				return;
			}

			if (readyfd == 0)
			{
				// no fd just early out
				return;
			}

			if (FD_ISSET(data.socket, &readset))
			{
				char msg[1024]{0};

				int bytes = recv(data.socket, msg, 1024, 0);

				if (bytes == SOCKET_ERROR)
				{
					continue;
				}

				for (auto& func : m_OnReceiveFuncs)
				{
					func(data, msg, bytes);
				}

			}

		}
	}
}