#pragma once

#include <jaguarcore\system\isystem.h>
#include <string>

namespace lpd
{
	class iDisplay;
	class GraphicsComponent;
	class CameraComponent;

	class MeshGroup;
	class SkeletalMesh;

	class iGraphicsSystem : public iSystem
	{
	public:
		virtual void SetDisplay(iDisplay* value) = 0;
		virtual iDisplay* GetDisplay() = 0;
		virtual GraphicsComponent* CreateGraphicsComponent() = 0;
		virtual CameraComponent* CreateCameraComponent() = 0;
		virtual MeshGroup* LoadMesh(const std::string& path) = 0;
		virtual SkeletalMesh* CreateSkeletalMesh() = 0;

		static iGraphicsSystem* CreateGraphicsSystem();

		void SetActiveCamera(const CameraComponent* cc) { m_ActiveCamera = cc; }
	protected:

		const CameraComponent* m_ActiveCamera = nullptr;
	};
}
