#pragma once
#include "jaguarcore/system/isystem.h"

namespace jgr
{
	class iEngine;

	class iScene : public iSystem
	{
		virtual iEngine* GetEngine() = 0;
	};
}
