#include <leopardgraphics/leopardpch.h>
#include <leopardgraphics/component/graphicscomponent.h>

#include "leopardgraphics/graphics/glgraphics/shader.h"
#include "leopardgraphics/graphics/glgraphics/draw.h"
#include "leopardgraphics/shapes/shape.h"
#include "jaguarcore/gameobject/gameobject.h"

namespace lpd
{
	void GraphicsComponent::Startup()
	{
		if (m_Shape)
		{
			m_Shape->Set();
		}
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
			const mat4& transform = GetGameObject()->GetTransform()->GetGlobalTransform();
			
			Uniform<mat4>::Set(shader.GetUniform("model"), transform * m_Shape->GetTransform());
			m_Shape->Bind(shader);
			m_Shape->Render(shader);
			m_Shape->Unbind(shader);
		}
	}
}
