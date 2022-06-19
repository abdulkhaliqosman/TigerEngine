#include <jaguarcore/jaguarpch.h>
#include "component.h"
#include "jaguarcore/gameobject/gameobject.h"

namespace jgr
{
	void Component::Startup()
	{

	}

	void Component::Update()
	{

	}

	void Component::Shutdown()
	{

	}

	TransformComponent* Component::GetTransform() 
	{ 
		return m_GameObject->GetTransform(); 
	}
}