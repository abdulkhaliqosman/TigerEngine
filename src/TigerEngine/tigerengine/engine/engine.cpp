#include <tigerengine/tigerpch.h>
#include <tigerengine/engine/engine.h>

#include <leopardgraphics/graphics/igraphicssystem.h>
#include "tigerengine/scene/scene.h"
#include "tigerengine/input/input.h"
#include <tigerengine/imgui/imguiwrapper.h>
#include "leopardgraphics/display/idisplay.h"

namespace tgr
{
	Engine::~Engine()
	{
		jgr::Delete(m_Input);
		jgr::Delete(m_Scene);
		jgr::Delete(m_Graphics);
		jgr::Delete(m_ImGuiWrapper);
	}

	void Engine::Startup()
	{
		// init
		m_Scene = jgr::New<Scene>();
		m_Input = jgr::New<Input>();

		m_Scene->SetEngine(this);

		// startup
		m_Input->Startup();
		m_Scene->Startup();
		m_Graphics->Startup();
		m_ImGuiWrapper->Startup();

	}

	void Engine::Update()
	{
		m_Input->Update();
		m_Scene->Update();
		m_Graphics->Update();
		m_ImGuiWrapper->Update();

		m_Graphics->GetDisplay()->SwapBuffers();
	}

	void Engine::Shutdown()
	{
		m_Input->Shutdown();
		m_Scene->Shutdown();
		m_Graphics->Shutdown();
		m_ImGuiWrapper->Shutdown();


	}
}
