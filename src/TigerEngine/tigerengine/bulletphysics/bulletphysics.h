#pragma once

#include "btBulletDynamicsCommon.h"
#include <tigerengine/bulletphysics/bulletrigidbody.h>

namespace tgr
{
	class BulletCollisionShape;

	class BulletPhysics : public iEngineSystem
	{
	public:
		inline BulletPhysics(iEngine& engine) :iEngineSystem(engine) {}
		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;

		BulletCollisionShape* CreateBoxShape(vec3 position, quat rotation, vec3 halfextents, float mass);
		BulletRigidBody* CreateRigidBody(vec3 pos, quat rot, float mass, BulletCollisionShape& shape);
		~BulletPhysics() {}

	private:
		btDefaultCollisionConfiguration* m_Config;
		btCollisionDispatcher* m_Dispatcher;
		btBroadphaseInterface* m_Broadphase;
		btSequentialImpulseConstraintSolver* m_Solver;

		btDiscreteDynamicsWorld* m_World;

		btAlignedObjectArray<btCollisionShape*> m_btCollisionShapes;

		BulletRigidBody* CreateRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);

		std::vector<BulletRigidBody*> m_RigidBodies;
		std::vector<BulletCollisionShape*> m_CollisionShapes;

	};

}