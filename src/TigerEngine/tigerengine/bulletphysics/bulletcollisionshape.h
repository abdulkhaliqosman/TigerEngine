#pragma once

namespace tgr
{
	class BulletCollisionShape
	{
	public:
		virtual btCollisionShape& GetbtShape() = 0;
	};
}