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

		inline const vec3& GetPosition() { return m_Position; }
		inline const quat& GetRotation() { return m_Rotation; }
		inline const vec3& GetScale() { return m_Scale; }

		inline void SetPosition(const vec3& t) { m_Position = t; }
		inline void SetRotation(const quat& r) { m_Rotation = r; }
		inline void SetScale(const vec3& s) { m_Scale = s; }

		inline const mat4& GetGlobalTransform() const { return m_GlobalTransform; }
		inline const void SetGlobalTransform(mat4& value) { m_GlobalTransform = value; }
		inline const mat4& GetLocalTransform() const { return m_LocalTransform; }
		inline const void SetLocalTransform(mat4& value) { m_LocalTransform = value; }

	private:
		vec3 m_Position = vec3::Zero();
		quat m_Rotation = quat::Identity();
		vec3 m_Scale = vec3::One();

		mat4 m_LocalTransform = mat4::Identity();
		mat4 m_GlobalTransform = mat4::Identity();
	};
}
