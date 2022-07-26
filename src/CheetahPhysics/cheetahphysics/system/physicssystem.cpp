#include <cheetahphysics/cheetahpch.h>
#include <cheetahphysics/system/physicssystem.h>
#include "btBulletDynamicsCommon.h"

namespace cht
{
	class BulletPhysics : public iPhysicsSystem
	{
		void Startup() override;
		void Update() override;
		void Shutdown() override;
	private:
		btDefaultCollisionConfiguration* m_Config;
		btCollisionDispatcher* m_Dispatcher;
		btBroadphaseInterface* m_Broadphase;
		btSequentialImpulseConstraintSolver* m_Solver;

		btDiscreteDynamicsWorld* m_World;
	};

	iPhysicsSystem* iPhysicsSystem::CreateBulletPhysics()
	{
		return jgrNew(BulletPhysics);
	}

	void BulletPhysics::Startup()
	{
		m_Config = jgrNew(btDefaultCollisionConfiguration);
		m_Dispatcher = jgrNew(btCollisionDispatcher, m_Config);
		m_Broadphase = jgrNew(btDbvtBroadphase);

		m_Solver = jgrNew(btSequentialImpulseConstraintSolver);

		m_World = jgrNew(btDiscreteDynamicsWorld, m_Dispatcher, m_Broadphase, m_Solver, m_Config);

		m_World->setGravity(btVector3(0, -10, 0));

	}

	void BulletPhysics::Update()
	{

	}

	void BulletPhysics::Shutdown()
	{
		jgrDelete(m_Config);
		jgrDelete(m_Dispatcher);
		jgrDelete(m_Broadphase);
		jgrDelete(m_Solver);
		jgrDelete(m_World);
	}
}