#include <leopardgraphics/leopardpch.h>
#include <leopardgraphics/component/cameracomponent.h>

#include <jaguarcore/math/camera.h>

namespace lpd
{
	void CameraComponent::Update()
	{
		SetPerspective();
	}

	void CameraComponent::SetOrthographic()
	{
		m_Projection = jgr::Camera::CreateOrthographicMatrix(m_NearPlane, m_FarPlane, m_Top, m_Right);
	}

	void CameraComponent::SetPerspective()
	{
		m_Projection = jgr::Camera::CreatePerspectiveMatrix(m_NearPlane, m_FarPlane, m_Top, m_Right);
	}
}
