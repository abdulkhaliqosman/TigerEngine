#include "tigerengine/tigerpch.h"
#include "winglcontext.h"

#include <glad/glad.h>

#include <gl/wglext.h>
#include <tigerengine/app/windows/winapp.h>
#include "backends/imgui_impl_win32.h"

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static tgr::WinGLContext* s_WinGLContext = nullptr;
namespace tgr
{

	void WinGLContext::MakeWindow(HINSTANCE hInstance, PSTR szCmdLine)
	{
		s_WinGLContext = this;

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

		m_HWND = hwnd;
	}

	void WinGLContext::CreateContext()
	{
		m_HDC = GetDC(m_HWND);

		// Create openGL context
		// 6. Find the correct pixel format and apply to device context
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(m_HDC, &pfd);
		SetPixelFormat(m_HDC, pixelFormat, &pfd);

		// 7. Create temp legacy opengl context
		HGLRC tempRC = wglCreateContext(m_HDC);
		wglMakeCurrent(m_HDC, tempRC);
		PFNWGLCREATECONTEXTATTRIBSARBPROC
			wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB =
			(PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress(
				"wglCreateContextAttribsARB");

		// 8. Create modern OpenGL 8.8 context
		const int attribList[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB,
			3,
			WGL_CONTEXT_MINOR_VERSION_ARB,
			3,
			WGL_CONTEXT_FLAGS_ARB,
			0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0,
		};

		HGLRC hglrc = wglCreateContextAttribsARB(m_HDC, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempRC);
		wglMakeCurrent(m_HDC, hglrc);

		// 9. Use glad to load gl
		if (!gladLoadGL())
		{
			JgrLogError("Could not initialize GLAD");
		}
		else
		{
			JgrLogDebug("OpenGL Version %d.%d", GLVersion.major, GLVersion.minor);
		}

		SetEnableVSync(true);

		ShowWindow(m_HWND, SW_SHOW);
		UpdateWindow(m_HWND);
	}

	void WinGLContext::Update()
	{
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	void WinGLContext::SwapBuffers()
	{
		::SwapBuffers(m_HDC);

		// if (GetVSyncEnabled())
		// {
		// 	glFinish();
		// }
	}

	void WinGLContext::DestroyWindow()
	{
		::DestroyWindow(m_HWND);
		s_WinGLContext = nullptr;
	}

	void WinGLContext::DestroyContext()
	{
		HGLRC hglrc = wglGetCurrentContext();
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
		ReleaseDC(m_HWND, m_HDC);
	}

	void WinGLContext::SetEnableVSync(bool value)
	{
		// 10. Check if vsync is supported
		PFNWGLGETEXTENSIONSSTRINGEXTPROC
			_wglGetExtensionsStringEXT =
			(PFNWGLGETEXTENSIONSSTRINGEXTPROC)
			wglGetProcAddress("wglGetExtensionsStringEXT");

		bool swapControlSupported = strstr(
			_wglGetExtensionsStringEXT(),
			"WGL_EXT_swap_control") != 0;

		if (swapControlSupported)
		{
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
				(PFNWGLSWAPINTERVALEXTPROC)
				wglGetProcAddress("wglSwapIntervalEXT");
			PFNWGLGETSWAPINTERVALEXTPROC
				wglGetSwapIntervalEXT =
				(PFNWGLGETSWAPINTERVALEXTPROC)
				wglGetProcAddress("wglGetSwapIntervalEXT");
			if (wglSwapIntervalEXT(value ? 1 : 0))
			{
				JgrLogDebug("Enabled vsync");
				m_EnableVSync = wglGetSwapIntervalEXT();
			}
			else
			{
				JgrLogDebug("Could not enable vsync");
			}
		}
		else
		{ // !swapControlSupported
			JgrLogError("WGL_EXT_swap_control not supported");
		}
	}

	lpd::Rect WinGLContext::GetClientRect() const
	{
		RECT clientRect;
		::GetClientRect(m_HWND, &clientRect);
		lpd::Rect result;

		result.left = clientRect.left;
		result.right = clientRect.right;
		result.top = clientRect.top;
		result.bottom = clientRect.bottom;

		return result;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam))
		return true;

	switch (iMsg)
	{
		// 2. handle close window case
	case WM_CLOSE:
		if (s_WinGLContext->GetHWND() == hwnd)
		{
			tgr::WinApp::GetInstance()->OnWindowClose();
		}
		break;

		// release opengl resources when window is destroyed
	case WM_DESTROY:
		//if (gVertexArrayObject != 0)
	{
		PostQuitMessage(0);
	}
	// else
	// {
	// 	std::cout << "Multiple destroy messages\n";
	// }
	break;
	case WM_INPUT:
		tgr::WinApp::GetInput().ProcessInput(lParam);
		break;
		// 4. ignore others
	// case WM_PAINT:
	// case WM_ERASEBKGND:
	// 	return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}