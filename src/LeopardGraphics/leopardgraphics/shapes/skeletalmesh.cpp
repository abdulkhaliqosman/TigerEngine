#include <leopardgraphics/leopardpch.h>
#include "leopardgraphics/shapes/skeletalmesh.h"
#include "lionanimation/animation/animpose.h"
#include "leopardgraphics/graphics/glgraphics/draw.h"

namespace lpd
{
	void SkeletalMesh::Set()
	{
		if (m_Mesh)
		{
			m_Mesh->Set();
		}
	}

	void SkeletalMesh::Bind(Shader& shader)
	{
		if (m_Mesh)
		{
			m_Mesh->Bind(shader);
		}
	}

	void SkeletalMesh::Unbind(Shader& shader)
	{
		if (m_Mesh)
		{
			m_Mesh->Unbind(shader);
		}
	}

	void SkeletalMesh::Render(Shader& shader)
	{
		if (m_Pose)
		{
			Uniform<mat4>::Set(shader.GetUniform("jointTransform"), m_Pose->GetJointTransforms());
			Uniform<bool>::Set(shader.GetUniform("hasPose"), true);
		}
		else
		{
			Uniform<bool>::Set(shader.GetUniform("hasPose"), false);
		}

		Draw(m_Mesh->m_ElementBuffer, DrawMode::Triangles);
	}
}