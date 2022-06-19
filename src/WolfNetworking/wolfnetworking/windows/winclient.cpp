#include "wolfnetworking/wolfpch.h"
#include "wolfnetworking/windows/winclient.h"

#include <ws2tcpip.h>

namespace wolf
{
	void WinClientJob::Execute()
	{
		// lazy version first, 1 thread execute
		m_Client.Receive();
	}

	bool WinClient::CreateSocket(const std::string& address, const std::string& port)
	{
		// 1. init addrinfo/sockaddr
		struct addrinfo* result = NULL, * ptr = NULL, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// 2. getaddrinfo
		int iResult;
		// Resolve the server address and port
		iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return false;
		}

		// 3. create socket
		SOCKET connectSocket = INVALID_SOCKET;

		// 4. call socket
		// Attempt to connect to the first address returned by
		// the call to getaddrinfo
		ptr = result;

		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		// 5. check for error
		if (connectSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}

		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			return false;
		}

		m_ClientData.socket = connectSocket;

		sockaddr_in sockname;
		int sz = sizeof(sockname);

		getsockname(connectSocket, reinterpret_cast<sockaddr*>(&sockname), &sz);

		m_ClientData.ipAddress = sockname.sin_addr.s_addr;

		return true;
	}

	void WinClient::Update()
	{

	}

	void WinClient::Disconnect()
	{
		int iResult;
		iResult = shutdown(m_ClientData.socket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(m_ClientData.socket);
			WSACleanup();
			return;
		}
	}

	void WinClient::Send(const char* buffer, int length)
	{
		int result = send(m_ClientData.socket, buffer, length, 0);
	}

	void WinClient::Receive()
	{
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100; // don't block too long, only 0.1 ms

		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(m_ClientData.socket, &readset);

		// as a start we receive socket once a frame only
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

		if (FD_ISSET(m_ClientData.socket, &readset))
		{
			char msg[1024]{ 0 };

			int bytes = recv(m_ClientData.socket, msg, 1024, 0);

			if (bytes == SOCKET_ERROR)
			{
				return;
			}

			for (auto& func : m_OnReceiveFuncs)
			{
				func(m_ClientData, msg, bytes);
			}

		}
	}
}