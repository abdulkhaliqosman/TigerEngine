#pragma once
#include <vector>
#include <jaguarcore/scene/iscene.h>

namespace jgr
{
	class GameObject;
	class TransformComponent;
}

namespace tgr
{
	class Engine;
	class Scene : public jgr::iScene
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline void SetEngine(Engine* value) { m_Engine = value; }

		jgr::GameObject* CreateGameObject();
		jgr::TransformComponent* CreateTransformComponent(jgr::GameObject*);


	private:
		std::vector<jgr::GameObject*> m_GameObjects;
		std::vector<jgr::TransformComponent*> m_TransformComponents;
		Engine* m_Engine;
	};
}