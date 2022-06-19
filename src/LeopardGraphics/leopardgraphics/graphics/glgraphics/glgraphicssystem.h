#pragma once

#include "jaguarcore/math/math.h"
#include "leopardgraphics/graphics/igraphicssystem.h"
#include "leopardgraphics/graphics/glgraphics/glgraphics.h"
#include "leopardgraphics/shapes/cube.h"

namespace lpd
{
	class iDisplay;
	class MeshGroup;
	class Shape;

	class GLGraphicsSystem : public iGraphicsSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void SetDisplay(iDisplay* value) override;
		iDisplay* GetDisplay() override;
		GraphicsComponent* CreateGraphicsComponent() override;
		CameraComponent* CreateCameraComponent() override;
		MeshGroup* LoadMesh(const std::string& path) override;
		SkeletalMesh* CreateSkeletalMesh() override;

	private:
		void ClearScreen();

		VertexArray m_VertexArray;
		Shader m_Shader;
		Cube m_Cube;

		iDisplay* m_Display;

		std::vector<GraphicsComponent*> m_GraphicsComponents;
		std::vector<CameraComponent*> m_CameraComponents;
		std::vector<Shape*> m_Shapes;
		std::vector<SkeletalMesh*> m_SkeletalMeshes;
	};
}
