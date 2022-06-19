#pragma once

#include "jaguarcore/components/component.h"

constexpr float TAN45 = 1.0f;
constexpr float DEFAULT_NEARPLANE = 0.001f;
constexpr float DEFAULT_FARPLANE = 1000.0f;
constexpr float ASPECT_RATIO_16_9 = 16.0f / 9.0f;

namespace lpd
{
	class CameraComponent : public jgr::Component
	{
	public:
		void Update();

		inline void SetNearPlane(float value) { m_NearPlane = value; }
		inline void SetFarPlane(float value) { m_FarPlane = value; }

		inline void SetTop(float value) { m_Top = value; }
		inline void SetRight(float value) { m_Right = value; }

		void SetOrthographic();
		void SetPerspective();

		inline const mat4& GetProjectionMatrix() const { return m_Projection; }

	private:
		mat4 m_Projection;

		float m_NearPlane = DEFAULT_NEARPLANE;
		float m_FarPlane = DEFAULT_FARPLANE;

		float m_Top = TAN45 * DEFAULT_NEARPLANE / ASPECT_RATIO_16_9;
		float m_Right = TAN45 * DEFAULT_NEARPLANE;
	};
}