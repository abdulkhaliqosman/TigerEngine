#include <leopardgraphics/leopardpch.h>
#include <leopardgraphics/shapes/staticshape.h>

namespace lpd
{
	StaticShape::StaticShape()
	{

	}

	StaticShape::StaticShape(StaticShape&& other)
		:m_PosAttrib(std::move(other.m_PosAttrib)),
		m_NormalAttrib(std::move(other.m_NormalAttrib)),
		m_ElementBuffer(std::move(other.m_ElementBuffer))
	{

	}

	void StaticShape::Set()
	{
		m_PosAttrib.Set(GetVertices(), GetVertexCount());
		m_NormalAttrib.Set(GetNormals(), GetNormalCount());
		m_ElementBuffer.Set(GetIndices(), GetIndexCount());
	}

	void StaticShape::Bind(Shader& shader)
	{
		GetPosAttrib().BindTo(shader.GetAttribute("position"));
		GetNormalAttrib().BindTo(shader.GetAttribute("normal"));

	}

	void StaticShape::Unbind(Shader& shader)
	{
		GetPosAttrib().UnBindFrom(shader.GetAttribute("position"));
		GetNormalAttrib().UnBindFrom(shader.GetAttribute("normal"));
	}

}
