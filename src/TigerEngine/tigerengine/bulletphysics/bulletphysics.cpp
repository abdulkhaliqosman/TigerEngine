#include <tigerengine/tigerpch.h>
#include <tigerengine/bulletphysics/bulletphysics.h>
#include <tigerengine/bulletphysics/bulletboxshape.h>

namespace tgr
{
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
			for (int i = m_World->getNumConstraints() - 1; i >= 0; i--)
			{
				m_World->removeConstraint(m_World->getConstraint(i));
			}
			for (int i = m_World->getNumCollisionObjects() - 1; i >= 0; i--)
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
			btCollisionShape* shape = m_btCollisionShapes[j];
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

		for (auto& body : m_RigidBodies)
		{
			body->Update();
		}

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


	BulletCollisionShape* BulletPhysics::CreateBoxShape(vec3 pos, quat rot, vec3 halfextents, float mass)
	{
		btVector3 position{pos.x(), pos.y(), pos.z()};
		btQuaternion rotation{ rot.x(), rot.y(), rot.z() };
		btTransform transform{ rotation, position };

		btVector3 halfext{ halfextents.x(), halfextents.y(), halfextents.z() };

		BulletBoxShape* box = new BulletBoxShape(halfextents);

		return box;
	}

	BulletRigidBody* BulletPhysics::CreateRigidBody(vec3 pos, quat rot, float mass, BulletCollisionShape& shape)
	{
		btVector3 position{ pos.x(), pos.y(), pos.z() };
		btQuaternion rotation{ rot.x(), rot.y(), rot.z() };
		btTransform transform{ rotation, position };

		BulletRigidBody* body = new BulletRigidBody(mass, transform, shape);

		m_World->addRigidBody(body->GetbtRigidBody());

		m_RigidBodies.push_back(body);

		return body;
	}
}