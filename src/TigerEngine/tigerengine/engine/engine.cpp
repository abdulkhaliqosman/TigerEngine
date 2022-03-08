#include <tigerengine/tigerpch.h>
#include <tigerengine/engine/engine.h>

#include <leopardgraphics/graphics/igraphicssystem.h>
#include "tigerengine/scene/scene.h"
#include "tigerengine/input/input.h"
#include <tigerengine/imgui/imguiwrapper.h>
#include "leopardgraphics/display/idisplay.h"
#include <lionanimation/system/animationsystem.h>
#include <jaguarcore/thread/jobsystem.h>

#include "optick.h"

namespace tgr
{
	Engine::~Engine()
	{
		jgr::Delete(m_Input);
		jgr::Delete(m_Scene);
		jgr::Delete(m_Graphics);
		jgr::Delete(m_Animation);
		jgr::Delete(m_ImGuiWrapper);
		jgr::Delete(m_JobSystem);
	}

	void Engine::Startup()
	{
		OPTICK_EVENT();
		// init
		m_JobSystem = jgr::New<jgr::JobSystem>();

		m_Scene = jgr::New<Scene>();
		m_Input = jgr::New<Input>();
		m_Animation = jgr::New<lion::AnimationSystem>();
		
		m_Scene->SetEngine(this);
		m_Animation->SetJobSystem(m_JobSystem);

		// startup
		m_JobSystem->Startup();
		m_Input->Startup();
		m_Scene->Startup();
		m_Animation->Startup();
		m_Graphics->Startup();
		// m_ImGuiWrapper->Startup();
	}

	void Engine::Update()
	{
		OPTICK_EVENT();
		// no need for jobsystem update (maybe)
		m_Input->Update();
		m_Scene->Update();
		m_Animation->Update();
		m_Graphics->Update();
		// m_ImGuiWrapper->Update();

		m_JobSystem->Update();

		m_Graphics->GetDisplay()->SwapBuffers();
	}

	void Engine::Shutdown()
	{
		m_Input->Shutdown();
		m_Scene->Shutdown();
		m_Animation->Shutdown();
		m_Graphics->Shutdown();
		// m_ImGuiWrapper->Shutdown();

		m_JobSystem->Shutdown();
	}
}
