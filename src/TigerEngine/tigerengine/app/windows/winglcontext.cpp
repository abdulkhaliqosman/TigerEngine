#include "tigerengine/tigerpch.h"
#include "winglcontext.h"

#include <glad/glad.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32.lib")

void WinGLContext::CreateContext(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);

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

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	// 7. Create temp legacy opengl context
	HGLRC tempRC = wglCreateContext(hdc);
	wglMakeCurrent(hdc, tempRC);
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

	HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, attribList);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempRC);
	wglMakeCurrent(hdc, hglrc);

	// 9. Use glad to load gl
	if (!gladLoadGL())
	{
		JgrLogError("Could not initialize GLAD");
	}
	else
	{
		JgrLogDebug("OpenGL Version %d.%d", GLVersion.major, GLVersion.minor);
	}

	// 10. Check if vsync is supported
	PFNWGLGETEXTENSIONSSTRINGEXTPROC
		_wglGetExtensionsStringEXT =
		(PFNWGLGETEXTENSIONSSTRINGEXTPROC)
		wglGetProcAddress("wglGetExtensionsStringEXT");

	bool swapControlSupported = strstr(
		_wglGetExtensionsStringEXT(),
		"WGL_EXT_swap_control") != 0;

	// 11. if vsync is supported enable it
	int vsync = 0;
	if (swapControlSupported)
	{
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
			(PFNWGLSWAPINTERVALEXTPROC)
			wglGetProcAddress("wglSwapIntervalEXT");
		PFNWGLGETSWAPINTERVALEXTPROC
			wglGetSwapIntervalEXT =
			(PFNWGLGETSWAPINTERVALEXTPROC)
			wglGetProcAddress("wglGetSwapIntervalEXT");
		if (wglSwapIntervalEXT(1))
		{
			JgrLogDebug("Enabled vsync");
			vsync = wglGetSwapIntervalEXT();
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

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}