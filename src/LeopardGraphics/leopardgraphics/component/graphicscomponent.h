#pragma once

#include "jaguarcore/components/component.h"

namespace lion
{
	class AnimPose;
}

namespace lpd
{
	class Shader;
	class Shape;

	class GraphicsComponent : public jgr::Component
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		LEOPARD_DLL void AddShape(Shape* shape);
		void Render(Shader& shader);

	private:
		Shape* m_Shape;
		lion::AnimPose* m_AnimPose;
	};
}
