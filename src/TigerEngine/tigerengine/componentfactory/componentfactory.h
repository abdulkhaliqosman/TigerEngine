#pragma once

#include <vector>
#include <unordered_map>
#include <string>

namespace tgr
{
	class ComponentContainerBase
	{

	};

	template<typename T>
	class ComponentContainer : ComponentContainerBase
	{
	public:
		T* CreateComponent()
		{
			T* component = jgr::New<T>();
			m_Container.push_back(component);

		}
	private:
		std::vector<T*> m_Container;
	};

	class ComponentFactory
	{
	public:
		template<typename T>
		void RegisterContainer(const ComponentContainer<T>* container)
		{
			auto iter = m_Containers.find(T::TypeString);
			if (iter == m_Containers.end())
			{
				m_Containers.insert(T::TypeString, container);
			}
		}

		template<typename T>
		T* CreateComponent()
		{
			ComponentFactoryMap::iterator iter = m_Containers.find(T::TypeString);
			if (iter != m_Containers.end())
			{
				return static_cast<ComponentContainer<T>*>(iter->second)->CreateComponent<T>();
			}

			return nullptr;
		}

	private:
		using ComponentFactoryMap = std::unordered_map<std::string, ComponentContainerBase*>;
		ComponentFactoryMap m_Containers;
	};
}