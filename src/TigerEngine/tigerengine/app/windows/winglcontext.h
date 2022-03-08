#pragma once
#include "leopardgraphics/display/idisplay.h"

#include <glad/glad.h>
#include <gl/wglext.h>

namespace tgr
{
	class WinGLContext
	{
	public:
		void MakeWindow(HINSTANCE hInstance, PSTR szCmdLine);
		void CreateContext();

		void Update();
		void SwapBuffers();

		void DestroyWindow();
		void DestroyContext();

		lpd::Rect GetClientRect() const;

		inline bool GetVSyncEnabled() const { return m_EnableVSync; }
		void SetEnableVSync(bool);
		inline void SetHWND(HWND hwnd) { m_HWND = hwnd; }
		inline HWND GetHWND() { return m_HWND; }
	private:

		bool m_EnableVSync = false;

		HWND m_HWND;
		HDC m_HDC;
	};

}
