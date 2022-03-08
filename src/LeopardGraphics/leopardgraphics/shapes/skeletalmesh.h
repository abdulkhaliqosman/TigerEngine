#pragma once

#include "leopardgraphics/shapes/mesh.h"

namespace lpd
{
	class SkeletalMesh : public Shape
	{
	public:
		void Set() override;
		void Bind(Shader& shader) override;
		void Unbind(Shader& shader) override;

		void Render(Shader& shader) override;

		inline void SetPose(const lion::AnimPose* pose) { m_Pose = pose; }
		inline void SetMesh(Mesh* mesh) { m_Mesh = mesh; }

	private:
		Mesh* m_Mesh;

		const lion::AnimPose* m_Pose;
	};
}