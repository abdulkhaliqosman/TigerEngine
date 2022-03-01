#pragma once

#include "jaguarcore/math/math.h"
#include "leopardgraphics/graphics/igraphicssystem.h"
#include "leopardgraphics/graphics/glgraphics/glgraphics.h"
#include "leopardgraphics/shapes/cube.h"

namespace lpd
{
	class iDisplay;

	class GLGraphicsSystem : public iGraphicsSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void SetDisplay(iDisplay* value) override;
		iDisplay* GetDisplay() override;
		GraphicsComponent* CreateGraphicsComponent() override;

	private:
		void ClearScreen();

		VertexArray m_VertexArray;
		Shader m_Shader;
		Cube m_Cube;

		iDisplay* m_Display;

		std::vector<GraphicsComponent*> m_GraphicsComponents;
	};
}
