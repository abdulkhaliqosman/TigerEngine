#pragma once
#include <vector>
#include <jaguarcore/thread/jobsystem.h>

namespace jgr
{
	class GameObject;
}

namespace tgr
{
	class AgentComponent;

	class AgentJob : public jgr::Job
	{
	public:
		AgentComponent* component;

		void Execute() override;
	};

	class AgentManager : public iSceneSystem
	{
	public:
		inline AgentManager(iScene& scene) : iSceneSystem{ scene } {}
		inline virtual ~AgentManager() {}

		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;


		AgentComponent* CreateAgentComponent(jgr::GameObject*);

		AgentComponent* GetNearestAgent(AgentComponent* sourceAgent) const;

	private:
		std::vector<AgentComponent*> m_Agents;

		std::vector<AgentJob*> m_Jobs;
	};
}
