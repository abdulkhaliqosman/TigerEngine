#include <leopardgraphics/leopardpch.h>
#include "leopardgraphics/shapes/mesh.h"

#include "leopardgraphics/graphics/glgraphics/glgraphics.h"
#include "leopardgraphics/graphics/glgraphics/draw.h"
#include "lionanimation/animation/animpose.h"

namespace lpd
{
	void Mesh::Set()
	{
		m_PosAttrib.Set(m_LocalPosition);
		m_NormalAttrib.Set(m_Normal);
		m_ElementBuffer.Set(m_Indices);

		m_JointsAttrib.Set(m_Joints);
		m_WeightsAttrib.Set(m_Weights);
	}

	void Mesh::Bind(Shader& shader)
	{
		m_PosAttrib.BindTo(shader.GetAttribute("position"));
		m_NormalAttrib.BindTo(shader.GetAttribute("normal"));
		m_JointsAttrib.BindTo(shader.GetAttribute("joints"));
		m_WeightsAttrib.BindTo(shader.GetAttribute("weights"));

	}

	void Mesh::Unbind(Shader& shader)
	{
		m_PosAttrib.UnBindFrom(shader.GetAttribute("position"));
		m_NormalAttrib.UnBindFrom(shader.GetAttribute("normal"));
		m_JointsAttrib.UnBindFrom(shader.GetAttribute("joints"));
		m_WeightsAttrib.UnBindFrom(shader.GetAttribute("weights"));
	}

	void Mesh::Render(Shader& shader)
	{
		Uniform<bool>::Set(shader.GetUniform("hasPose"), false);

		Draw(m_ElementBuffer, DrawMode::Triangles);
	}

	void MeshGroup::Bind(Shader& shader)
	{
		for (auto* mesh : m_Meshes)
		{
			mesh->Bind(shader);
		}
	}

	void MeshGroup::Unbind(Shader& shader)
	{
		for (auto* mesh : m_Meshes)
		{
			mesh->Unbind(shader);
		}
	}

	void MeshGroup::Set()
	{
		for (auto* mesh : m_Meshes)
		{
			mesh->Set();
		}
	}

	void MeshGroup::Render(Shader& shader)
	{
		for (auto* mesh : m_Meshes)
		{
			mesh->Render(shader);
		}
	}
}