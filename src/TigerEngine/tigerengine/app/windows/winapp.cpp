#include <tigerengine/tigerpch.h>
#include <tigerengine/app/windows/winapp.h>

#include <tigerengine/engine/engine.h>
#include <leopardgraphics/graphics/igraphicssystem.h>

#include <tigerengine/app/windows/winglcontext.h>
#include <tigerengine/imgui/windows/winimguiwrapper.h>
#include <optick.h>

#include <wolfnetworking/windows/winnetworksystem.h>

namespace tgr
{
	WinApp* WinApp::ms_Instance = nullptr;

	WinApp::WinApp()
		:m_WinInput{*this}
	{

	}

	WinApp::~WinApp()
	{

	}

	void WinApp::Startup(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
	{
		m_hInstance = hInstance;
		m_hPrevInstance = hPrevInstance;
		m_szCmdLine = szCmdLine;
		m_iCmdShow = iCmdShow;

		ms_Instance = this;

		jgr::Memory::Startup();
	}

	void WinApp::Run()
	{
		Engine engine{*this};

		{
			OPTICK_FRAME("Startup");
			m_WinGLContext.MakeWindow(m_hInstance, m_szCmdLine);
			m_WinGLContext.CreateContext();

			m_WinInput.RegisterRawInputDevices(m_WinGLContext.GetHWND());

			auto* gfx = lpd::iGraphicsSystem::CreateGLGraphicsSystem(engine);
			gfx->SetDisplay(this);

			engine.SetGraphics(gfx);

			auto imgui = jgrNew(WinImGuiWrapper, engine);
			engine.SetImGuiWrapper(imgui);
			imgui->SetContext(&m_WinGLContext);

			engine.SetNetwork(jgrNew(wolf::WinNetworkSystem, engine));

			engine.Setup();

			m_IsRunning = true;
		}

		while (m_IsRunning)
		{
			OPTICK_FRAME("MainThread");
			m_WinGLContext.Update();
			engine.Update();
		}

		engine.Teardown();
	}

	void WinApp::Shutdown()
	{
		jgr::Memory::Shutdown();
	}

	void WinApp::OnWindowClose()
	{
		if (m_IsRunning)
		{
			m_WinGLContext.DestroyWindow();
			JgrLogDebug("Shutting Down");
			m_IsRunning = false;
		}
	}

	void WinApp::OnWindowDestroyed()
	{
		m_WinGLContext.DestroyContext();
	}

	lpd::Rect WinApp::GetClientRect() const
	{
		RECT clientRect;
		return m_WinGLContext.GetClientRect();
	}

	bool WinApp::IsVsyncEnabled() const
	{
		return m_WinGLContext.GetVSyncEnabled();
	}

	void WinApp::SwapBuffers()
	{
		OPTICK_EVENT();
		m_WinGLContext.SwapBuffers();
	}
}
