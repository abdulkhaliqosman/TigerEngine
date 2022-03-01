#pragma once
#include <jaguarcore\system\isystem.h>

namespace lpd
{
	class iDisplay;
	class GraphicsComponent;

	class iGraphicsSystem : public jgr::iSystem
	{
	public:
		virtual void SetDisplay(iDisplay* value) = 0;
		virtual iDisplay* GetDisplay() = 0;
		virtual GraphicsComponent* CreateGraphicsComponent() = 0;

		LEOPARD_DLL static iGraphicsSystem* CreateGraphicsSystem();
	};
}
