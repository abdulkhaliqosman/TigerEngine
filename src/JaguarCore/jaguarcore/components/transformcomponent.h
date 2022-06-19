#pragma once
#include "jaguarcore/math/math.h"
#include "jaguarcore/components/component.h"

namespace jgr
{
	class TransformComponent : public Component
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline const vec3& GetLocalPosition() { return m_LocalPosition; }
		inline const quat& GetLocalRotation() { return m_Rotation; }
		inline const vec3& GetLocalScale() { return m_Scale; }

		void SetLocalPosition(const vec3& t);
		void SetLocalRotation(const quat& r);
		void SetLocalScale(const vec3& s);

		inline const mat4& GetGlobalTransform() const { return m_GlobalTransform; }
		inline const mat4& GetLocalTransform() const { return m_LocalTransform; }

		inline vec3 Left() { return vec3{ m_LocalTransform[0].x(), m_LocalTransform[0].y(), m_LocalTransform[0].z() }; }
		inline vec3 Right() { return -Left(); }
		inline vec3 Up() { return vec3(m_LocalTransform[1].x(), m_LocalTransform[1].y(), m_LocalTransform[1].z()); }
		inline vec3 Down() { return -Up(); }
		inline vec3 Forward() { return vec3(m_LocalTransform[2].x(), m_LocalTransform[2].y(), m_LocalTransform[2].z()); }
		inline vec3 Back() { return -Forward(); }

	private:
		vec3 m_LocalPosition = vec3::Zero();
		quat m_Rotation = quat::Identity();
		vec3 m_Scale = vec3::One();

		mat4 m_LocalTransform = mat4::Identity();
		mat4 m_GlobalTransform = mat4::Identity();

		void UpdateTransforms();
	};
}
