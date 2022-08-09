#pragma once

#include <cheetahphysics/rigidbody/irigidbody.h>

namespace cht
{

	class iPhysicsSystem : public iEngineSystem
	{
	public:
		inline iPhysicsSystem(iEngine& engine) : iEngineSystem(engine) {}
		inline ~iPhysicsSystem() {}

		virtual iRigidBody* AddBoxRigidBody(vec3 position, quat rotation, vec3 halfextents, float mass) = 0;

		static iPhysicsSystem* CreateBulletPhysics(iEngine& engine);
	};
}