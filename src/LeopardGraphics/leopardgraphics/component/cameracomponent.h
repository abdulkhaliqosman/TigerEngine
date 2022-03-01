#pragma once

#include "jaguarcore/components/component.h"

namespace lpd
{
	class CameraComponent : public jgr::Component
	{
	public:
		mat4 m_Projection;

		static mat4 CreatePerspectiveMatrix(float near, float far, float top, float right);
		static mat4 CreateOrthoMatrix(float near, float far, float top, float right);
	};
}