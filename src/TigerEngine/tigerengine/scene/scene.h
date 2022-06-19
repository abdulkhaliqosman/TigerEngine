#pragma once
#include <vector>
#include <jaguarcore/scene/iscene.h>
#include <tigerengine/agents/agentmanager.h>
#include <tigerengine/engine/engine.h>

namespace jgr
{
	class GameObject;
	class TransformComponent;
}

namespace tgr
{
	class Scene : public jgr::iScene
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void SetEngine(Engine* value) { m_Engine = value; }
		jgr::iEngine* GetEngine() override { return m_Engine; }

		jgr::GameObject* CreateGameObject();
		jgr::TransformComponent* CreateTransformComponent(jgr::GameObject*);
		
		inline AgentManager& GetAgentManager() { return m_AgentManager; }
		
		template<typename T>
		T* CreateGenericComponent(jgr::GameObject* go)
		{
			T* comp = jgr::New <T>();
			go->AddComponent(comp);
			m_GenericComponents.push_back(comp);
			return comp;
		}

	private:
		std::vector<jgr::GameObject*> m_GameObjects;
		std::vector<jgr::TransformComponent*> m_TransformComponents;
		std::vector<jgr::Component*> m_GenericComponents;
		Engine* m_Engine;

		AgentManager m_AgentManager;

	};
}