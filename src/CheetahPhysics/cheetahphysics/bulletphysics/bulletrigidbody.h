#pragma once

#include <cheetahphysics/rigidbody/irigidbody.h>

namespace cht
{
	class BulletRigidBody : public iRigidBody
	{
	public:
		BulletRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);

		inline float GetMass() const override { return m_Mass; }
		void SetMass(float value) override;

		inline btRigidBody* GetbtRigidBody() { return m_btRigidBody; }
	private:
		float m_Mass = 0;

		btRigidBody* m_btRigidBody;
	};
}