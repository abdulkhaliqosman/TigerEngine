#pragma once
#include <jaguarcore\input\iinputsystem.h>

namespace tgr
{
	class WinInput : public jgr::iInputSystem
	{
	public:
		inline WinInput(iApp& app) : iInputSystem(app) {}
		inline virtual ~WinInput() {}

		void Setup() override;
		void Teardown() override;

		void Update() override;

		inline bool GetKeyDown(int vKey) const { return m_Keys[vKey]; }
		bool m_Keys[256] = { false };

		void RegisterRawInputDevices(HWND hWnd);
		void ProcessInput(LPARAM lParam);
	};
}