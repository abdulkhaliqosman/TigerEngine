#include <jaguarcore/jaguarpch.h>
#include "jaguarcore/gameobject/gameobject.h"

namespace jgr
{
	void GameObject::AddComponent(Component* component)
	{
		m_Components.push_back(component);
		component->SetGameObject(this);
	}
}
