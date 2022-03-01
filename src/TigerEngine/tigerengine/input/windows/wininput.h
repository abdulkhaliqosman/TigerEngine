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
	};
}