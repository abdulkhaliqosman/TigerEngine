#include <tigerengine/tigerpch.h>
#include <tigerengine/engine/engine.h>

#include <leopardgraphics/graphics/igraphicssystem.h>
#include <tigerengine/scene/scene.h>
#include <tigerengine/imgui/imguiwrapper.h>
#include <leopardgraphics/display/idisplay.h>
#include <lionanimation/system/animationsystem.h>
#include <jaguarcore/thread/jobsystem.h>
#include <wolfnetworking/system/inetworksystem.h>

#include "tigerengine/gamenetwork/gamenetworksystem.h"

#include "wolfnetworking/imgui/networkimguipage.h"

#include "optick.h"

namespace tgr
{
	Engine::~Engine()
	{
		jgr::Delete(m_Scene);
		jgr::Delete(m_Graphics);
		jgr::Delete(m_Animation);
		jgr::Delete(m_ImGuiWrapper);
		jgr::Delete(m_JobSystem);
		jgr::Delete(m_Network);
		jgr::Delete(m_GameNetwork);
	}

	void Engine::Startup()
	{
		OPTICK_EVENT();
		// init
		m_JobSystem = jgr::New<jgr::JobSystem>();
		m_Animation = jgr::New<lion::AnimationSystem>();
		m_Scene = jgr::New<Scene>();

		m_GameNetwork = jgr::New<GameNetworkSystem>();
		
		m_Scene->SetEngine(this);
		m_Animation->SetJobSystem(m_JobSystem);
		m_GameNetwork->SetNetworkSystem(m_Network);

		SetupDebugPages();

		// startup
		m_Scene->Startup(); // we bootstrap the world data first

		// Core systems first
		m_JobSystem->Startup();
		m_Animation->Startup();
		m_Graphics->Startup();
		m_Network->Startup();

		// Gameplay systems next
		m_GameNetwork->Startup();
		
		// Finally debug systems
		m_ImGuiWrapper->Startup();
	}

	void Engine::Update()
	{
		OPTICK_EVENT();

		// no need for jobsystem update (maybe)
		m_Scene->Update();
		
		m_Animation->Update();
		m_Graphics->Update();
		
		m_Network->Update();

		m_ImGuiWrapper->Update();

		m_JobSystem->Update();

		m_Graphics->GetDisplay()->SwapBuffers();
	}

	void Engine::Shutdown()
	{
		m_Scene->Shutdown();
		m_Animation->Shutdown();
		m_Graphics->Shutdown();
		m_Network->Shutdown();
		m_ImGuiWrapper->Shutdown();

		m_JobSystem->Shutdown();
	}

	void Engine::SetupDebugPages()
	{
		auto* networkPage = jgr::New<wolf::NetworkImguiPage>();
		networkPage->SetNetworkSystem(m_Network);
		m_ImGuiWrapper->AddImguiPage(networkPage);
	}
}
