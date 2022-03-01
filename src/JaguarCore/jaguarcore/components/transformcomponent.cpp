#include <jaguarcore/jaguarpch.h>
#include "transformcomponent.h"

namespace jgr
{
	void TransformComponent::Startup()
	{

	}

	void TransformComponent::Update()
	{
		m_LocalTransform = jgr::Transform::CreateTransformMatrix(m_Position, m_Rotation, m_Scale);
		m_GlobalTransform = m_LocalTransform;
	}

	void TransformComponent::Shutdown()
	{

	}
}