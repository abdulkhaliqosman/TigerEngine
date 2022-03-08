#pragma once
#include <jaguarcore\system\isystem.h>

namespace jgr
{
	class JobSystem;
}

namespace lpd
{
	class iGraphicsSystem;
}

namespace lion
{
	class AnimationSystem;
}

namespace tgr
{
	class Input;
	class Scene;
	class ImGuiWrapper;

	class Engine : public jgr::iSystem
	{
	public:
		~Engine();

		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline void SetGraphics(lpd::iGraphicsSystem* value) { m_Graphics = value; }
		inline void SetImGuiWrapper(ImGuiWrapper* value) { m_ImGuiWrapper = value; }

		inline Scene* GetScene() { return m_Scene; }
		inline lpd::iGraphicsSystem* GetGraphics() { return m_Graphics; }
		inline lion::AnimationSystem* GetAnimation() { return m_Animation; }

		inline ImGuiWrapper* GetImGuiWrapper() { return m_ImGuiWrapper; }
		inline jgr::JobSystem* GetJobSystem() { return m_JobSystem; }

		

	private:
		Input* m_Input = nullptr;
		lpd::iGraphicsSystem* m_Graphics = nullptr;
		lion::AnimationSystem* m_Animation = nullptr;
		Scene* m_Scene = nullptr;
		ImGuiWrapper* m_ImGuiWrapper = nullptr;
		jgr::JobSystem* m_JobSystem = nullptr;
	};
}
