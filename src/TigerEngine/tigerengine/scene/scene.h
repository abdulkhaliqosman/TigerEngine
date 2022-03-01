#pragma once
#include <vector>
#include <jaguarcore/scene/iscene.h>

namespace jgr
{
	class GameObject;
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

	private:
		std::vector<jgr::GameObject*> m_GameObjects;
		Engine* m_Engine;
	};
}