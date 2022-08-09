#include <cheetahphysics/cheetahpch.h>

#include "btBulletDynamicsCommon.h"
#include <cheetahphysics/bulletphysics/bulletrigidbody.h>

namespace cht
{
	BulletRigidBody::BulletRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
		:m_Mass{mass}, m_btRigidBody{nullptr}
	{
		btAssert((shape != nullptr || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape->calculateLocalInertia(mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
		btRigidBody* body = new btRigidBody(cInfo);

		body->setUserIndex(-1);
		m_btRigidBody = body;
	}

	void BulletRigidBody::SetMass(float value) 
	{ 
		m_Mass = value; 

	}
}