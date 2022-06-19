#pragma once
#include <jaguarcore\input\iinput.h>

namespace tgr
{
	class WinInput : public jgr::iInput
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline bool GetKeyDown(int vKey) const { return m_Keys[vKey]; }
		bool m_Keys[256] = { false };

		void RegisterRawInputDevices(HWND hWnd);
		void ProcessInput(LPARAM lParam);
	};
}