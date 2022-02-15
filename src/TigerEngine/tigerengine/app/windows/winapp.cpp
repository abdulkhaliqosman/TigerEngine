#include <tigerengine/tigerpch.h>
#include "winapp.h"

#include <tigerengine/engine/engine.h>
#include <leopardgraphics/graphics/glgraphics/glgraphics.h>
#include <tigerengine/app/windows/winglcontext.h>

HWND MakeWindow(HINSTANCE, PSTR szCmdLine);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

tgr::WinApp g_WinApp;


namespace tgr
{
	void WinApp::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
	{
		m_hInstance = hInstance;
		m_hPrevInstance = hPrevInstance;
		m_szCmdLine = szCmdLine;
		m_iCmdShow = iCmdShow;
	}

	void WinApp::Run()
	{
		Engine engine;
		lpd::GLGraphics* graphics = jgr::New<lpd::GLGraphics>();
		engine.Startup();

		m_HWND = MakeWindow(m_hInstance, m_szCmdLine);

		WinGLContext::CreateContext(m_HWND);

		m_IsRunning = true;
		while (m_IsRunning)
		{

		}
	}

	void WinApp::OnWindowClose()
	{
		if (m_IsRunning)
		{
			DestroyWindow(m_HWND);
			JgrLogDebug("Shutting Down");
			m_IsRunning = false;
		}
	}

	void WinApp::OnWindowDestroyed()
	{

	}
}

HWND MakeWindow(HINSTANCE hInstance, PSTR szCmdLine)
{
	int clientWidth = 1280;
	int clientHeight = 720;

	// 2. wndclassex
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = 0;
	wndclass.lpszClassName = L"Win32 Game Window";
	RegisterClassEx(&wndclass);

	// 3. window width and heights
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT windowRect;
	SetRect(&windowRect, (screenWidth / 2) - (clientWidth / 2),
		(screenHeight / 2) - (clientHeight / 2),
		(screenWidth / 2) + (clientWidth / 2),
		(screenHeight / 2) + (clientHeight / 2));

	// 4. Set window style

	DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX);
	// | WS_THICKFRAME to resize

	// 5. Call func to adjust the window, and create the windowEx
	AdjustWindowRectEx(&windowRect, style, FALSE, 0);
	HWND hwnd = CreateWindowEx(
		0, wndclass.lpszClassName, L"Game Window", style, windowRect.left,
		windowRect.top, windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, NULL, NULL, hInstance, szCmdLine);

	return hwnd;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		// 2. handle close window case
	case WM_CLOSE:
		if (g_WinApp.GetHWND() == hwnd)
		{
			g_WinApp.OnWindowClose();
		}
		break;

		// release opengl resources when window is destroyed
	case WM_DESTROY:
		//if (gVertexArrayObject != 0)
	{
		HDC hdc = GetDC(hwnd);
		// HGLRC hglrc = wglGetCurrentContext();
		// glBindVertexArray(0);
		// glDeleteVertexArrays(1, &gVertexArrayObject);
		// gVertexArrayObject = 0;
		// wglMakeCurrent(NULL, NULL);
		// wglDeleteContext(hglrc);
		// ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
	}
	// else
	// {
	// 	std::cout << "Multiple destroy messages\n";
	// }
	break;
	case WM_INPUT:
		return 0;
		// 4. ignore others
	case WM_PAINT:
	case WM_ERASEBKGND:
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}