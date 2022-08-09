#pragma once

namespace jgr
{
	class Scene;

	class iSceneSystem : public jgr::iSystem
	{
	public:
		inline iSceneSystem(iScene& scene) : m_Scene{ scene } {}
		inline virtual ~iSceneSystem() {}

		inline iScene& GetScene() { return m_Scene; }

		virtual void StartScene() = 0;
		virtual void StopScene() = 0;

	private:
		iScene& m_Scene;
	};
}