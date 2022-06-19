#pragma once
#include <vector>
#include "jaguarcore/components/transformcomponent.h"

namespace jgr
{
	class Component;
	class iScene;

	class GameObject
	{
	public:
		inline void SetTransform(TransformComponent* transform) { m_Transform = transform; }
		inline TransformComponent* GetTransform() { return m_Transform; }

		void AddComponent(Component* component);

		template<typename T>
		T* GetComponent();
		inline iScene* GetScene() { return m_Scene; }
		inline void SetScene(iScene* value) { m_Scene = value; }

	private:
		std::vector<Component*> m_Components;
		TransformComponent* m_Transform;
		iScene* m_Scene;
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
