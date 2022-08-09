#include <tigerengine/tigerpch.h>
#include <tigerengine/agents/agentmanager.h>
#include <tigerengine/agents/agentcomponent.h>

#include "jaguarcore/gameobject/gameobject.h"

#include "optick.h"
#include <tigerengine/scene/scene.h>
#include <tigerengine/engine/engine.h>

namespace tgr
{
	void AgentJob::Execute()
	{
		OPTICK_EVENT();
		component->Update();
	}

	void AgentManager::Setup()
	{
		for (auto* elem : m_Agents)
		{
			elem->Startup();
			auto* job = jgr::New<AgentJob>();
			job->component = elem;
			m_Jobs.push_back(job);
		}
	}

	void AgentManager::Teardown()
	{
		for (auto* agent : m_Agents)
		{
			jgr::Delete(agent);
		}
	}

	void AgentManager::StartScene()
	{

	}

	void AgentManager::StopScene()
	{

	}

	void AgentManager::Update()
	{
		OPTICK_EVENT();
		for (auto* elem : m_Jobs)
		{
			GetScene().GetJobSystem().PushJob(elem);
		}
	}

	AgentComponent* AgentManager::CreateAgentComponent(jgr::GameObject* gameObject)
	{
		auto* agent = jgr::New<AgentComponent>();
		gameObject->AddComponent(agent);
		m_Agents.push_back(agent);
		agent->SetAgentManager(this);

		return agent;
	}

	AgentComponent* AgentManager::GetNearestAgent(AgentComponent* sourceAgent) const
	{
		// Dumb version, iterating a for loop. No partitioning

		if (m_Agents.size() < 2)
		{
			return nullptr;
		}

		const vec3& sourcePosition = sourceAgent->GetTransform()->GetLocalPosition();

		AgentComponent* nearestAgent = nullptr;
		float nearestSqDistance = FLT_MAX;

		for (auto* targetAgent : m_Agents)
		{
			if (targetAgent == sourceAgent)
			{
				continue;
			}

			const vec3& targetPosition = targetAgent->GetTransform()->GetLocalPosition();
			float lengthSq = (targetPosition - sourcePosition).LengthSquared();
			if (lengthSq < nearestSqDistance)
			{
				nearestAgent = targetAgent;
				nearestSqDistance = lengthSq;
			}
		}

		return nearestAgent;
	}
}