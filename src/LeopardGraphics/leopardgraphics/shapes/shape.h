#pragma once
#include "jaguarcore/math/math.h"
#include "leopardgraphics/graphics/glgraphics/glgraphics.h"

namespace lpd
{
	class Shape
	{
	public:
		virtual void Set() = 0;
		virtual void Bind(Shader& shader) = 0;
		virtual void Unbind(Shader& shader) = 0;

	private:
		Attribute<vec3> m_PosAttrib;
		Attribute<vec3> m_NormalAttrib;
		ElementBuffer m_ElementBuffer;
	};

}
