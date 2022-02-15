#pragma once
#include <jaguarcore\system\isystem.h>

namespace tgr
{
	class Engine : public jgr::iSystem
	{
	public:
		void Startup();

		void Update();

		void Shutdown();

	private:

	};
}
