#pragma once
#include <jaguarcore\system\isystem.h>

namespace tgr
{
	class Input : public jgr::iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;
	};
}