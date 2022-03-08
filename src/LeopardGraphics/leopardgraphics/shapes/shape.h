#pragma once
#include "jaguarcore/math/math.h"
#include "leopardgraphics/graphics/glgraphics/glgraphics.h"

namespace lpd
{
	class Shape
	{
	public:
		inline virtual ~Shape() {}

		virtual void Set() = 0;
		virtual void Bind(Shader& shader) = 0;
		virtual void Unbind(Shader& shader) = 0;
		virtual void Render(Shader& shader) = 0;

		inline const std::string& GetPath() const { return m_Path; }
		inline void SetPath(const std::string& path) { m_Path = path; }
	private:
		Attribute<vec3> m_PosAttrib;
		Attribute<vec3> m_NormalAttrib;
		ElementBuffer m_ElementBuffer;
		std::string m_Path;
	};

}
