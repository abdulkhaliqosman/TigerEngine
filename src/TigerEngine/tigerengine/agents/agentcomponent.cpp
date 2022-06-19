#include <tigerengine/tigerpch.h>
#include <tigerengine/agents/agentcomponent.h>
#include <tigerengine/agents/agentmanager.h>

namespace tgr
{
	void AgentComponent::Startup()
	{

	}

	void AgentComponent::Update()
	{
		// get nearest
		AgentComponent* other = m_AgentManager->GetNearestAgent(this);

		// walk to it

		auto* transform = GetTransform();
		vec3 pos = transform->GetLocalPosition();
		
		auto* otherTransform = other->GetTransform();
		vec3 otherPos = otherTransform->GetLocalPosition();

		// if touching do stuff

		float distSq = (pos - otherPos).LengthSquared();
		constexpr float touchingSqDist = 0.5f * 0.5f;
		if (distSq <= touchingSqDist)
		{
			JgrLogDebug("touch");
		}

	}

	void AgentComponent::Shutdown()
	{

	}
}