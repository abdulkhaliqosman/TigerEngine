#pragma once

#include <jaguarcore\system\isystem.h>

namespace tgr
{
	class ImGuiWrapper : public jgr::iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;
	private:

		bool m_ShowDemoWindow = true;
	};
}