#pragma once
#include <vector>
#include "jaguarcore/components/transformcomponent.h"

namespace jgr
{
	class Component;
	class Scene;

	class GameObject
	{
	public:
		inline void SetTransform(TransformComponent* transform) { m_Transform = transform; }
		inline TransformComponent* GetTransform() { return m_Transform; }

		void AddComponent(Component* component);

		template<typename T>
		T* GetComponent();
		inline Scene* GetOwner() { return m_Owner; }
		inline void GetOwner(Scene* value) { m_Owner = value; }
	private:
		std::vector<Component*> m_Components;
		TransformComponent* m_Transform;
		Scene* m_Owner;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		for (Component* component : m_Components)
		{
			T* t = dynamic_cast<T*>(component); // yes everyone says dynamic cast is slow and evil but I dont care it's a small engine
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
}
