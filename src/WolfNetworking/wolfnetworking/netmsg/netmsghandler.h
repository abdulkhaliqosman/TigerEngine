#pragma once

#include <unordered_map>
#include <wolfnetworking/netmsg/netmsg.h>

namespace wolf
{
	class iNetworkSystem;

	class NetMsgHandler
	{
	public:

		template<typename T>
		void RegisterNetMsgType(std::function<void(const T&)> onMsgReceivedCallback)
		{
			auto iter = m_NetMsgMap.find(T::s_NetMsgTypeId);
			NetMsgFactory<T>* factory = nullptr;
			if (iter == m_NetMsgMap.end())
			{
				factory = jgr::New<NetMsgFactory<T> >();

				m_NetMsgMap[T::s_NetMsgTypeId] = factory;
			}
			else
			{
				iNetMsgFactory* ifac = iter->second;
				factory = dynamic_cast<NetMsgFactory<T>*>(ifac);
			}

			factory->RegisterReceivedCallback(onMsgReceivedCallback);
		}

		void OnReceivePacket(const NetClientData&, const char* data, int length);
		
		void SendNetMsgToServer(iNetMsg& msg);
		void SendNetMsgToClient(NetUserId destId, iNetMsg& msg);
		void BroadcastNetMsgToClients(iNetMsg& msg);

		NetMsgHandler() = default;

		void SetNetworkSystem(iNetworkSystem* value) { m_NetworkSystem = value; }

	private:
		void InitNetMsgHeader(iNetMsg& msg);

		class iNetMsgFactory
		{
		public:
			virtual void CreateReceivedNetMsg(const NetMsgReadVisitor& visitor) = 0;
		};

		template<typename T>
		class NetMsgFactory : public iNetMsgFactory
		{
		public:
			NetMsgFactory(){}

			void RegisterReceivedCallback(std::function<void(const T&)> onMsgReceivedCallback)
			{
				m_OnMsgReceivedCallback.push_back(onMsgReceivedCallback);
			}

			void CreateReceivedNetMsg(const NetMsgReadVisitor& visitor) override
			{
				T* netMsg = jgr::New<T>();
				netMsg->Deserialize(visitor);

				for (auto& callback : m_OnMsgReceivedCallback)
				{
					callback(*netMsg);
				}
			}

		private:
			std::vector<std::function<void(const T&)> > m_OnMsgReceivedCallback;
		};

		NetMsgHandler(const NetMsgHandler&) = delete;
		std::unordered_map< NetMsgTypeId, iNetMsgFactory*> m_NetMsgMap;

		iNetworkSystem* m_NetworkSystem;
	};
}