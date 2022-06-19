#pragma once

namespace tgr
{
	class AgentManager;

	class AgentComponent : public Component
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline const AgentManager* GetAgentManager() const { return m_AgentManager; }
		inline void SetAgentManager(const AgentManager* value) { m_AgentManager = value; }
	
	private:
		const AgentManager* m_AgentManager = nullptr;
	};
}
