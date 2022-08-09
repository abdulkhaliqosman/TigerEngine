#include <cheetahphysics/cheetahpch.h>
#include "btBulletDynamicsCommon.h"
#include <cheetahphysics/bulletphysics/bulletphysics.h>

namespace cht
{
	iPhysicsSystem* iPhysicsSystem::CreateBulletPhysics(iEngine& engine)
	{
		return jgrNew(BulletPhysics, engine);
	}

	void BulletPhysics::Setup()
	{
		m_Config = jgrNew(btDefaultCollisionConfiguration);
		m_Dispatcher = jgrNew(btCollisionDispatcher, m_Config);
		m_Broadphase = jgrNew(btDbvtBroadphase);

		m_Solver = jgrNew(btSequentialImpulseConstraintSolver);

		m_World = jgrNew(btDiscreteDynamicsWorld, m_Dispatcher, m_Broadphase, m_Solver, m_Config);
	}

	void BulletPhysics::Teardown()
	{
		//remove the rigidbodies from the dynamics world and delete them

		if (m_World)
		{
			int i;
			for (i = m_World->getNumConstraints() - 1; i >= 0; i--)
			{
				m_World->removeConstraint(m_World->getConstraint(i));
			}
			for (i = m_World->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = m_World->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				m_World->removeCollisionObject(obj);
				delete obj;
			}
		}

		//delete collision shapes
		for (int j = 0; j < m_CollisionShapes.size(); j++)
		{
			btCollisionShape* shape = m_CollisionShapes[j];
			delete shape;
		}

		jgrDelete(m_World);
		jgrDelete(m_Solver);
		jgrDelete(m_Config);
		jgrDelete(m_Broadphase);
		jgrDelete(m_Dispatcher);
	}

	void BulletPhysics::StartScene()
	{
		m_World->setGravity(btVector3(0, -10, 0));
	}

	void BulletPhysics::StopScene()
	{

	}

	void BulletPhysics::Update()
	{
		m_World->stepSimulation(1.0f / 60.0f);

		bool print = false;
		if (print)
		{
			// print positions of all objects
			for (int j = m_World->getNumCollisionObjects() - 1; j >= 0;j--)
			{
				btCollisionObject* obj = m_World->getCollisionObjectArray()[j];
				btRigidBody* body = btRigidBody::upcast(obj);
				btTransform trans;

				if (body && body->getMotionState())
				{
					body->getMotionState()->getWorldTransform(trans);
				}
				else
				{
					trans = obj->getWorldTransform();
				}

				printf("world pos object %d = %f, %f, %f\n", j, float(trans.getOrigin().getX()),
					float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			}
		}
	}


	iRigidBody* BulletPhysics::AddBoxRigidBody(vec3 pos, quat rot, vec3 halfextents, float mass)
	{
		btVector3 position{pos.x(), pos.y(), pos.z()};
		btQuaternion rotation{ rot.x(), rot.y(), rot.z() };
		btTransform transform{ rotation, position };

		btVector3 halfext{ halfextents.x(), halfextents.y(), halfextents.z() };

		btBoxShape* box = new btBoxShape(halfext);
		
		m_CollisionShapes.push_back(box);

		return CreateRigidBody(mass, transform, box);
	}

	iRigidBody* BulletPhysics::CreateRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		BulletRigidBody* body = new BulletRigidBody(mass, startTransform, shape);

		m_World->addRigidBody(body->GetbtRigidBody());

		return body;
	}
}