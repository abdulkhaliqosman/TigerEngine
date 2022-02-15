#pragma once
#include "jaguarcore/app/iapp.h"

#include <windows.h>

namespace tgr
{
	class WinApp : public jgr::iApp
	{
	public:
		void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
		void Run() override;

		void OnWindowClose() override;
		void OnWindowDestroyed() override;

		inline void SetHWND(HWND hwnd) { m_HWND = hwnd; }
		inline HWND GetHWND() { return m_HWND; }

	private:
		HINSTANCE m_hInstance;
		HINSTANCE m_hPrevInstance;
		PSTR m_szCmdLine; 
		int m_iCmdShow;

		HWND m_HWND;
		bool m_IsRunning = false;
	};
}
