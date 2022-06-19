#include <jaguarcore/jaguarpch.h>
#include <jaguarcore/components/transformcomponent.h>

namespace jgr
{
	void TransformComponent::Startup()
	{

	}

	void TransformComponent::Update()
	{
		
	}

	void TransformComponent::Shutdown()
	{

	}

	void TransformComponent::SetLocalPosition(const vec3& t) 
	{ 
		m_LocalPosition = t;
		UpdateTransforms();
	}

	void TransformComponent::SetLocalRotation(const quat& r) 
	{ 
		m_Rotation = r;
		UpdateTransforms();
	}

	void TransformComponent::SetLocalScale(const vec3& s) 
	{ 
		m_Scale = s;
		UpdateTransforms();
	}

	void TransformComponent::UpdateTransforms()
	{
		m_LocalTransform = jgr::Transform::CreateTransformMatrix(m_LocalPosition, m_Rotation, m_Scale);
		m_GlobalTransform = m_LocalTransform;
	}
}