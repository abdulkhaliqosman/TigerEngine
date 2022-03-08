#pragma once

#include "jaguarcore/components/component.h"

namespace lpd
{
	class CameraComponent : public jgr::Component
	{
	public:
		inline void SetNearPlane(float value) { m_NearPlane = value; }
		inline void SetFarPlane(float value) { m_FarPlane = value; }

		inline void SetTop(float value) { m_Top = value; }
		inline void SetRight(float value) { m_Right = value; }

		void SetOrthographic();
		void SetPerspective();

		inline const mat4& GetProjectionMatrix() const { return m_Projection; }
	private:
		mat4 m_Projection;

		float m_NearPlane;
		float m_FarPlane; 

		float m_Top; 
		float m_Right;
	};
}