#pragma once
#include <jaguarcore\system\isystem.h>

namespace lpd
{
	class iGraphicsSystem;
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
		inline lpd::iGraphicsSystem* GetGraphics() { return m_Graphics; }

		inline void SetImGuiWrapper(ImGuiWrapper* value) { m_ImGuiWrapper = value; }
		inline ImGuiWrapper* GetImGuiWrapper() { return m_ImGuiWrapper; }

	private:
		Input* m_Input = nullptr;
		lpd::iGraphicsSystem* m_Graphics = nullptr;
		Scene* m_Scene = nullptr;
		ImGuiWrapper* m_ImGuiWrapper;
	};
}
