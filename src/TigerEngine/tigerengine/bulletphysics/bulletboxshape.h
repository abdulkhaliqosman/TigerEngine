#pragma once

#include <tigerengine/bulletphysics/bulletcollisionshape.h>

namespace tgr
{
	class BulletBoxShape : public BulletCollisionShape
	{
	public:
		inline BulletBoxShape(vec3 halfextents):m_bt(btVector3{ halfextents.x(), halfextents.y(), halfextents.z() }){}

		inline btBoxShape& GetbtBox() { return m_bt; }
		inline btCollisionShape& GetbtShape() override { return m_bt; }
	private:
		btBoxShape m_bt;
	};
}