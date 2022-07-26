#pragma once

#include <jaguarcore\engine\iengine.h>

namespace cht
{

	class iPhysicsSystem : public jgr::iSystem
	{
	public:
		static iPhysicsSystem* CreateBulletPhysics();
	};
}