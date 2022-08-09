#pragma once

#include <cheetahphysics/system/iphysicssystem.h>
#include <cheetahphysics/bulletphysics/bulletrigidbody.h>

namespace cht
{
	class BulletPhysics : public iPhysicsSystem
	{
	public:
		inline BulletPhysics(iEngine& engine) :iPhysicsSystem(engine) {}
		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;

		iRigidBody* AddBoxRigidBody(vec3 position, quat rotation, vec3 halfextents, float mass) override;
		~BulletPhysics() {}

	private:
		btDefaultCollisionConfiguration* m_Config;
		btCollisionDispatcher* m_Dispatcher;
		btBroadphaseInterface* m_Broadphase;
		btSequentialImpulseConstraintSolver* m_Solver;

		btDiscreteDynamicsWorld* m_World;

		btAlignedObjectArray<btCollisionShape*> m_CollisionShapes;

		iRigidBody* CreateRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);

		std::vector<BulletRigidBody*> m_RigidBodies;

	};

}