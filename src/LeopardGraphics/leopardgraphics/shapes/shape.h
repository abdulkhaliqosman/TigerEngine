#pragma once
#include "jaguarcore/math/math.h"
#include "leopardgraphics/graphics/glgraphics/glgraphics.h"

namespace lpd
{
	class Shape
	{
	public:
		inline virtual ~Shape() {}

		virtual void Set() = 0;
		virtual void Bind(Shader& shader) = 0;
		virtual void Unbind(Shader& shader) = 0;
		virtual void Render(Shader& shader) = 0;

		inline const std::string& GetPath() const { return m_Path; }
		inline void SetPath(const std::string& path) { m_Path = path; }

		inline vec3 GetPosition() const { return m_Position; }
		inline quat GetRotation() const { return m_Rotation; }
		inline vec3 GetScale() const { return m_Scale; }

		inline mat4 GetTransform() const { return jgr::Transform::CreateTransformMatrix(m_Position, m_Rotation, m_Scale); }

		inline void SetPosition(const vec3& val) { m_Position = val; }
		inline void SetRotation(const quat& val) { m_Rotation = val; }
		inline void SetScale(const vec3& val) { m_Scale = val; }

	private:
		vec3 m_Position = vec3::Zero();
		quat m_Rotation = quat::Identity();
		vec3 m_Scale = vec3::One();
		
		Attribute<vec3> m_PosAttrib;
		Attribute<vec3> m_NormalAttrib;
		ElementBuffer m_ElementBuffer;
		std::string m_Path;
	};

}
