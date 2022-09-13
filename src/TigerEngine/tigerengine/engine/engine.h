#pragma once

#include <jaguarcore\engine\iengine.h>

namespace lpd
{
	class iGraphicsSystem;
}

namespace lion
{
	class AnimationSystem;
}

namespace wolf
{
	class iNetworkSystem;
}

namespace tgr
{
	class Scene;
	class ImGuiWrapper;
	class GameNetworkSystem;
	class BulletPhysics;

	class Engine : public iEngine
	{
	public:
		inline Engine(iApp& app) :iEngine{ app } {}
		virtual ~Engine();

		void Setup() override;
		void Teardown() override;

		void Update() override;

		inline void SetGraphics(lpd::iGraphicsSystem* value) { m_Graphics = value; }
		inline void SetNetwork(wolf::iNetworkSystem* value) { m_Network = value; }
		inline void SetInput(jgr::iInput* value) { m_Input = value; }
		inline void SetImGuiWrapper(ImGuiWrapper* value) { m_ImGuiWrapper = value; }

		inline Scene* GetScene() { return m_Scene; }

		inline lpd::iGraphicsSystem* GetGraphics() { return m_Graphics; }
		inline wolf::iNetworkSystem* GetNetwork() { return m_Network; }
		inline GameNetworkSystem* GetGameNetwork() { return m_GameNetwork; }
		inline lion::AnimationSystem* GetAnimation() { return m_Animation; }
		inline BulletPhysics* GetPhysics() { return m_Physics; }

		inline ImGuiWrapper* GetImGuiWrapper() { return m_ImGuiWrapper; }
		inline jgr::JobSystem& GetJobSystem() override { return *m_JobSystem; }
		inline jgr::iInput& GetInput() override { return *m_Input; }

	private:
		void SetupDebugPages();

		lpd::iGraphicsSystem* m_Graphics = nullptr;
		jgr::iInput* m_Input = nullptr;
		wolf::iNetworkSystem* m_Network = nullptr;
		GameNetworkSystem* m_GameNetwork = nullptr;
		lion::AnimationSystem* m_Animation = nullptr;
		Scene* m_Scene = nullptr;
		ImGuiWrapper* m_ImGuiWrapper = nullptr;
		jgr::JobSystem* m_JobSystem = nullptr;
		BulletPhysics* m_Physics = nullptr;
	};
}
