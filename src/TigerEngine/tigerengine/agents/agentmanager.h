#pragma once
#include <vector>
#include <tigerengine/scene/iscenesystem.h>
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
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		AgentComponent* CreateAgentComponent(jgr::GameObject*);

		AgentComponent* GetNearestAgent(AgentComponent* sourceAgent) const;

	private:
		std::vector<AgentComponent*> m_Agents;

		std::vector<AgentJob*> m_Jobs;
	};
}
