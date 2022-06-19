#include "wolfnetworking/wolfpch.h"
#include "wolfnetworking/imgui/networkimguipage.h"

#include <imgui.h>

#include "wolfnetworking/system/inetworksystem.h"
#include "wolfnetworking/system/inetworkserver.h"
#include "wolfnetworking/system/inetworkclient.h"
#include <functional>
#include <sstream>
#include <wolfnetworking/netmsg/netmsghandler.h>

namespace wolf
{
	void NetworkImguiPage::Startup()
	{
		std::function<void(const TestNetMsg&)> func = [this](const TestNetMsg& msg)
		{
			this->OnReceive(msg);
		};

		m_NetworkSystem->GetMsgHandler().RegisterNetMsgType(func);
	}

	void NetworkImguiPage::Update()
	{
		ImGui::Begin("Network");
		ImGui::Text("Hello, world!");

		static char addressBuffer[32]{ 0 };
		static char textbox[1024]{ 0 };


		switch (m_NetworkSystem->GetCurrentNetworkType())
		{
		case NetworkType::Client:
		{
			ImGui::Text("Running as Client");

			auto* client = m_NetworkSystem->GetClient();
			ImGui::Text(m_NetworkSystem->IpIntToString(client->GetClientData().ipAddress).c_str());

			ImGui::InputText("Text to Send", textbox, 1024);

			if (ImGui::Button("Send Text"))
			{
				TestNetMsg msg;
				msg.SetTestMessage(textbox);

				m_NetworkSystem->GetMsgHandler().SendNetMsgToServer(msg);
			}

			if (ImGui::Button("Disconnect"))
			{
				m_NetworkSystem->Disconnect();
			}

			DisplayChat();

			break;
		}
		case NetworkType::Server:
		{
			ImGui::Text("Running as Server");

			auto* server = m_NetworkSystem->GetServer();
			ImGui::Text(m_NetworkSystem->IpIntToString(server->GetServerData().ipAddress).c_str());

			ImGui::InputText("Text to Send", textbox, 1024);

			std::vector<const NetClientData*> clientsdata = server->GetClientsData();
			for (const NetClientData* client : clientsdata)
			{
				ImGui::Text("userId: %d", client->userId);
				ImGui::Text(m_NetworkSystem->IpIntToString(client->ipAddress).c_str());
				std::stringstream ss;
				ss << "Send to Client " << client->userId << std::endl;

				if (ImGui::Button(ss.str().c_str()))
				{
					TestNetMsg msg;
					msg.SetTestMessage(textbox);

					m_NetworkSystem->GetMsgHandler().SendNetMsgToClient(client->userId, msg);
				}
			}

			if (ImGui::Button("Disconnect"))
			{
				m_NetworkSystem->Disconnect();
			}

			DisplayChat();

			break;
		}
		case NetworkType::Disabled:
		{
			if (ImGui::Button("Start Server"))
			{
				m_NetworkSystem->StartServer();
			}

			ImGui::InputText("Server To Join", addressBuffer, 32);
			if (ImGui::Button("Start Client"))
			{
				m_NetworkSystem->StartClient(addressBuffer);
			}
			break;
		}
		}

		ImGui::End();
	}

	void NetworkImguiPage::OnReceive(const TestNetMsg& src)
	{
		std::string chatEntry;

		std::string ipAddress = m_NetworkSystem->NetUserIdToString(src.GetNetMsgHeader().sourceId);

		chatEntry = ipAddress + ": " + src.GetTestMessage();

		m_Chatlog.push_back(chatEntry);
	}

	void NetworkImguiPage::DisplayChat()
	{
		for (const auto& chat : m_Chatlog)
		{
			ImGui::Text(chat.c_str());
		}
	}

	void TestNetMsg::Serialize(NetMsgWriteVisitor& visitor) const
	{
		int length = m_Message.length();
		super::Serialize(visitor);
		visitor.Write(length);
		visitor.WriteBuffer(m_Message.c_str(), length);
	}

	void TestNetMsg::Deserialize(const NetMsgReadVisitor& visitor)
	{
		int length = 0;
		char text[128] = "";

		super::Deserialize(visitor);
		visitor.Read(length);
		// assert size less than 128

		visitor.ReadBuffer(text, length);
		text[length] = 0;
		m_Message = text;
	}

	int TestNetMsg::GetPacketSize() const
	{
		int superSize = super::GetPacketSize();
		int lengthSize = sizeof(int);
		int msgSize = m_Message.length();
		return superSize + lengthSize + msgSize;
	}
}