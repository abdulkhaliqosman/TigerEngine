#pragma once

#include "jaguarcore/app/iapp.h"
#include "leopardgraphics/display/idisplay.h"

#include <windows.h>
#include <tigerengine/app/windows/winglcontext.h>
#include <tigerengine/app/windows/wininput.h>

namespace tgr
{
	class WinApp : public jgr::iApp, public lpd::iDisplay
	{
	public:
		void Startup(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
		void Run() override;
		void Shutdown();

		void OnWindowClose() override;
		void OnWindowDestroyed() override;

		lpd::Rect GetClientRect() const override;
		bool IsVsyncEnabled() const override;
		void SwapBuffers() override;
		
		inline static WinApp* GetInstance() { return ms_Instance; }
		inline static WinInput& GetInput() { return GetInstance()->m_WinInput; } // TODO: Maybe make this generic

	private:
		HINSTANCE m_hInstance;
		HINSTANCE m_hPrevInstance;
		PSTR m_szCmdLine; 
		int m_iCmdShow;

		bool m_IsRunning = false;

		WinGLContext m_WinGLContext;
		WinInput m_WinInput;
		static WinApp* ms_Instance;
	};
}
