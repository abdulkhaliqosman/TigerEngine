#pragma once

namespace tgr
{
	
	class BulletCollisionShape;

	class BulletRigidBody : public Component
	{
	public:
		BulletRigidBody(float mass, const btTransform& startTransform, BulletCollisionShape& shape);

		void Update() override;

		inline float GetMass() const { return m_Mass; }
		void SetMass(float value);

		inline btRigidBody* GetbtRigidBody() { return m_btRigidBody; }
	private:
		float m_Mass = 0;

		btRigidBody* m_btRigidBody;
	};
}