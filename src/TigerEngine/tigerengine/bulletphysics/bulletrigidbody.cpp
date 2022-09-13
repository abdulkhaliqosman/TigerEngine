#include <tigerengine/tigerpch.h>

#include "btBulletDynamicsCommon.h"
#include <tigerengine/bulletphysics/bulletrigidbody.h>
#include <tigerengine/bulletphysics/bulletcollisionshape.h>

namespace tgr
{
	BulletRigidBody::BulletRigidBody(float mass, const btTransform& startTransform, BulletCollisionShape& shape)
		:m_Mass{mass}, m_btRigidBody{nullptr}
	{
		btAssert(shape.GetbtShape().getShapeType() != INVALID_SHAPE_PROXYTYPE);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape.GetbtShape().calculateLocalInertia(mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, &shape.GetbtShape(), localInertia);
		btRigidBody* body = new btRigidBody(cInfo);

		body->setUserIndex(-1);
		m_btRigidBody = body;
	}

	void BulletRigidBody::Update()
	{
		btTransform btTrans;

		if (m_btRigidBody && m_btRigidBody->getMotionState())
		{
			m_btRigidBody->getMotionState()->getWorldTransform(btTrans);
		}
		else
		{
			btTrans = m_btRigidBody->getWorldTransform();
		}

		jgr::TransformComponent* tc = GetTransform();

		btVector3& pos = btTrans.getOrigin();
		btQuaternion rot = btTrans.getRotation();

		tc->SetLocalPosition(vec3(pos.x(), pos.y(), pos.z()));
		tc->SetLocalRotation(quat(rot.x(), rot.y(), rot.z(), rot.w()));
	}

	void BulletRigidBody::SetMass(float value) 
	{ 
		m_Mass = value; 

	}
}