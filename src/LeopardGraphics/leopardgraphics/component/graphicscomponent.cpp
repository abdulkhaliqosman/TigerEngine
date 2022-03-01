#include <leopardgraphics/leopardpch.h>
#include <leopardgraphics/component/graphicscomponent.h>

#include "leopardgraphics/graphics/glgraphics/shader.h"
#include "leopardgraphics/graphics/glgraphics/draw.h"
#include "leopardgraphics/shapes/shape.h"
#include "jaguarcore/gameobject/gameobject.h"
#include "lionanimation/animation/animpose.h"

namespace lpd
{
	void GraphicsComponent::Startup()
	{

	}

	void GraphicsComponent::Update()
	{

	}

	void GraphicsComponent::Shutdown()
	{

	}

	void GraphicsComponent::AddShape(Shape* shape)
	{
		m_Shape = shape;
	}

	void GraphicsComponent::Render(Shader& shader)
	{
		if (m_Shape)
		{
			m_Shape->Bind(shader);
		}

		if (m_AnimPose)
		{
			Uniform<mat4>::Set(shader.GetUniform("jointTransform"), m_AnimPose->GetJointTransforms());
			Uniform<bool>::Set(shader.GetUniform("hasPose"), true);
		}
		else
		{
			Uniform<bool>::Set(shader.GetUniform("hasPose"), false);
		}
			
		const mat4& transform = GetGameObject()->GetTransform()->GetGlobalTransform();
		Uniform<mat4>::Set(shader.GetUniform("model"), transform);
	}
}
