#pragma once
#include <jaguarcore/components/component.h>

namespace wolf
{
	class iNetworkSystem;

	class NetComponent : public jgr::Component
	{
	public:
		inline void SetNetwork(wolf::iNetworkSystem* value) { m_Network = value; }
		inline wolf::iNetworkSystem* GetNetwork() { return m_Network; }

	private:
		iNetworkSystem* m_Network = nullptr;
	};

}