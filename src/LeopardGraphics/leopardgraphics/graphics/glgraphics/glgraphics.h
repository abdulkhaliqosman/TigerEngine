#pragma once

#include "leopardgraphics/graphics/igraphics.h"

namespace lpd
{
	class GLGraphics : public iGraphics
	{
	public:
		LEOPARD_DLL void Startup() override;
		LEOPARD_DLL void Update() override;
		LEOPARD_DLL void Shutdown() override;
	};
}
