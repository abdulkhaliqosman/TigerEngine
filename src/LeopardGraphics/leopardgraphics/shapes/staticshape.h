#pragma once

#include <leopardgraphics/shapes/shape.h>

namespace lpd
{
	class StaticShape : public Shape
	{
	public:
		StaticShape();
		StaticShape(StaticShape&& other);

		void Set() override;
		void Bind(Shader& shader) override;
		void Unbind(Shader& shader) override;
		void Render(Shader& shader) override;

		virtual const vec3* GetVertices() const = 0;
		virtual unsigned int GetVertexCount() const = 0;

		virtual const vec3* GetNormals() const = 0;
		virtual unsigned int GetNormalCount() const = 0;

		virtual const unsigned int* GetIndices() const = 0;
		virtual unsigned int GetIndexCount() const = 0;

		inline const Attribute<vec3>& GetPosAttrib() const { return m_PosAttrib; }
		inline const Attribute<vec3>& GetNormalAttrib() const { return m_NormalAttrib; }
		
		inline const ElementBuffer& GetElementBuffer() const { return m_ElementBuffer; }

	private:
		Attribute<vec3> m_PosAttrib;
		Attribute<vec3> m_NormalAttrib;

		ElementBuffer m_ElementBuffer;
	};
}
