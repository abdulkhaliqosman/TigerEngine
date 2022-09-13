#include <tigerengine/tigerpch.h>
#include <tigerengine/engine/engine.h>

#include <leopardgraphics/graphics/igraphicssystem.h>
#include <tigerengine/scene/scene.h>
#include <tigerengine/imgui/imguiwrapper.h>
#include <leopardgraphics/display/idisplay.h>
#include <lionanimation/system/animationsystem.h>
#include <jaguarcore/thread/jobsystem.h>
#include <wolfnetworking/system/inetworksystem.h>
#include <tigerengine/bulletphysics/bulletphysics.h>

#include "tigerengine/gamenetwork/gamenetworksystem.h"

#include "wolfnetworking/imgui/networkimguipage.h"

#include "optick.h"

namespace tgr
{
	Engine::~Engine()
	{
		jgrDelete(m_Scene);
		jgrDelete(m_Graphics);
		jgrDelete(m_Animation);
		jgrDelete(m_Physics);
		jgrDelete(m_JobSystem);
		jgrDelete(m_Network);
		jgrDelete(m_GameNetwork);
		jgrDelete(m_ImGuiWrapper);
	}

	void Engine::Setup()
	{
		OPTICK_EVENT();

		// init
		m_JobSystem = jgrNew(jgr::JobSystem, *this);
		m_Animation = jgrNew(lion::AnimationSystem, *this);
		m_Physics = jgrNew(BulletPhysics, *this);

		m_Scene = jgrNew(Scene, *this);

		m_GameNetwork = jgrNew(GameNetworkSystem, *this);
		
		// resolve dependencies
		m_Scene->SetEngine(this);
		m_Animation->SetJobSystem(m_JobSystem);
		m_GameNetwork->SetNetworkSystem(m_Network);

		SetupDebugPages();


		// startup
		m_Physics->Setup();
		m_Scene->Setup(); // we bootstrap the world data first
		                    // TODO: move world data to Init() or create a scene manager

		// Core systems first
		m_JobSystem->Setup();
		m_Animation->Setup();
		m_Graphics->Setup();
		m_Network->Setup();

		// Gameplay systems next
		m_GameNetwork->Setup();
		
		// Finally debug systems
		m_ImGuiWrapper->Setup();
	}

	void Engine::Update()
	{
		OPTICK_EVENT();

		m_ImGuiWrapper->Update();

		m_Scene->Update();
		m_Network->Update();
		
		m_Physics->Update();

		m_Animation->Update();
		m_Graphics->Update();
		


		m_JobSystem->Update();

		m_Graphics->GetDisplay()->SwapBuffers();
	}

	void Engine::Teardown()
	{
		m_ImGuiWrapper->Teardown();

		m_JobSystem->Teardown(); // kill the job system first in case of other system dependencies
		
		m_GameNetwork->Teardown();
		m_Network->Teardown();

		m_Physics->Teardown();

		m_Animation->Teardown();
		m_Graphics->Teardown();


		m_Scene->Teardown(); // scene is last like how it was first
		                     // TODO: create an UnInit
	}

	void Engine::SetupDebugPages()
	{
		auto* networkPage = jgr::New<wolf::NetworkImguiPage>();
		networkPage->SetNetworkSystem(m_Network);
		m_ImGuiWrapper->AddImguiPage(networkPage);
	}
}
