#pragma once

namespace tgr
{
	class Scene;

	class iSceneSystem : public jgr::iSystem
	{
	public:
		inline void SetScene(Scene* scene) { m_Scene = scene; }
		inline Scene* GetScene() { return m_Scene; }
	private:
		Scene* m_Scene = nullptr;
	};
}