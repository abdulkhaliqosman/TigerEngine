#pragma once

#include "matrix.h"

namespace jgr
{
	namespace Camera
	{
		inline mat4 CreatePerspectiveMatrix(float nearPlane, float farPlane, float top, float right)
		{
			mat4 result;

			result[0][0] = nearPlane / right;
			result[1][1] = nearPlane / top;
			result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
			result[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
			result[2][3] = -1;

			return result;
		}

		inline mat4 CreateOrthographicMatrix(float nearPlane, float farPlane, float top, float right)
		{
			mat4 result;

			result[0][0] = 1 / right;
			result[1][1] = 1 / top;
			result[2][2] = -2 / (farPlane - nearPlane);
			result[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
			result[3][3] = -1;

			return result;
		}
	}
}