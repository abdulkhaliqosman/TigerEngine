#include <tigerengine/tigerpch.h>

#define QWORD __int64
#include "windows.h"

#include "winuser.h"
#include <iostream>

#include <tigerengine/gameplay/cameramovementcomponent.h>
#include <tigerengine/app/windows/winapp.h>
#include <jaguarcore/components/transformcomponent.h>

namespace tgr
{
	void CameraMovementComponent::Startup()
	{
		
	}

	void CameraMovementComponent::Update()
	{
		auto* transform = GetTransform();
		const auto& localPos = transform->GetLocalPosition();

		if (WinApp::GetInput().GetKeyDown('W'))
		{
			transform->SetLocalPosition(localPos + transform->Forward() / 60.0f);
		}

		if (WinApp::GetInput().GetKeyDown('S'))
		{
			transform->SetLocalPosition(localPos + transform->Back() / 60.0f);
		}

		if (WinApp::GetInput().GetKeyDown('A'))
		{
			transform->SetLocalPosition(localPos + transform->Left() / 60.0f);
		}

		if (WinApp::GetInput().GetKeyDown('D'))
		{
			transform->SetLocalPosition(localPos + transform->Right() / 60.0f);
		}

		if (WinApp::GetInput().GetKeyDown(VK_UP))
		{
			m_Rotation.pitch += 1.0f;
			transform->SetLocalRotation(quat::FromEulerAngles(m_Rotation));
		}

		if (WinApp::GetInput().GetKeyDown(VK_DOWN))
		{
			m_Rotation.pitch -= 1.0f;
			transform->SetLocalRotation(quat::FromEulerAngles(m_Rotation));
		}

		if (WinApp::GetInput().GetKeyDown(VK_LEFT))
		{
			m_Rotation.yaw += 1.0f;
			transform->SetLocalRotation(quat::FromEulerAngles(m_Rotation));
		}

		if (WinApp::GetInput().GetKeyDown(VK_RIGHT))
		{
			m_Rotation.yaw -= 1.0f;
			transform->SetLocalRotation(quat::FromEulerAngles(m_Rotation));
		}
	}

	void CameraMovementComponent::Shutdown()
	{
		
	}

}