#include <tigerengine/tigerpch.h>
#include <tigerengine/app/windows/winapp.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);

#if _DEBUG
#pragma comment(linker, "/subsystem:console")
int main(int argc, const char** argv)
{
	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(),
		SW_SHOWDEFAULT);
}
#else
#pragma comment(linker, "/subsystem:windows")
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	tgr::WinApp winApp;
	winApp.Startup(hInstance, hPrevInstance, szCmdLine, iCmdShow);
	winApp.Run();
}
