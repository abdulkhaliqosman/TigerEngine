#pragma once


#include <string>
#include <leopardgraphics/shapes/cube.h>

namespace lpd
{
	class iDisplay;
	class GraphicsComponent;
	class CameraComponent;

	class MeshGroup;
	class SkeletalMesh;
	class Cube;

	class iGraphicsSystem : public iEngineSystem
	{
	public:
		inline iGraphicsSystem(iEngine& engine) : iEngineSystem(engine) {}
		inline virtual ~iGraphicsSystem() {}

		virtual void SetDisplay(iDisplay* value) = 0;
		virtual iDisplay* GetDisplay() = 0;
		virtual GraphicsComponent* CreateGraphicsComponent() = 0;
		virtual CameraComponent* CreateCameraComponent() = 0;
		virtual MeshGroup* LoadMesh(const std::string& path) = 0;

		virtual SkeletalMesh* CreateSkeletalMesh() = 0;
		virtual Cube* CreateCube() = 0;

		virtual Cube* GetUnitCube() = 0;
		static iGraphicsSystem* CreateGLGraphicsSystem(iEngine& engine);

		void SetActiveCamera(const CameraComponent* cc) { m_ActiveCamera = cc; }
	protected:

		const CameraComponent* m_ActiveCamera = nullptr;
	};
}
