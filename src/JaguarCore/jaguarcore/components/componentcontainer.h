#pragma once

#include <vector>

namespace jgr
{
	template<typename T>
	class ComponentContainer
	{
	public:
		~ComponentContainer()
		{
			for (T* elem : m_Components)
			{
				jgr::Delete(elem);
			}
		}

		T* CreateComponent()
		{
			if (!m_InactiveComponents.empty())
			{
				T* component = m_InactiveComponents.back();
				m_InactiveComponents.pop_back();
				return component;
			}

			T* component = jgrNew(T);
			m_Components.push_back(component);
			m_StartupComponents.push_back(component);
		}

		void StartupComponents()
		{
			for (T* elem : m_StartupComponents)
			{
				elem->Startup();
				m_ActiveComponents.push_back(elem);
			}
			m_StartupComponents.clear();
		}

		void UpdateComponents()
		{
			for (T* elem : m_ActiveComponents)
			{
				elem->Update();
			}
		}

		void ShutdownComponents()
		{
			for (T* elem : m_ShutdownComponents)
			{
				elem->Shutdown();
				m_InactiveComponents.push_back(elem);
			}
			m_ShutdownComponents.clear();
		}

	private:
		std::vector<T*> m_Components;
		std::vector<T*> m_StartupComponents;
		std::vector<T*> m_ActiveComponents;
		std::vector<T*> m_ShutdownComponents;
		std::vector<T*> m_InactiveComponents;
	};
}