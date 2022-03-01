#include <leopardgraphics/leopardpch.h>
#include <leopardgraphics/component/cameracomponent.h>

namespace lpd
{
	mat4 CameraComponent::CreatePerspectiveMatrix(float nearPlane, float farPlane, float top, float right)
	{
		mat4 result;

		result[0][0] = nearPlane / right;
		result[1][1] = nearPlane / top;
		result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		result[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
		result[2][3] = -1;

		return result;
	}

	mat4 CameraComponent::CreateOrthoMatrix(float nearPlane, float farPlane, float top, float right)
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
