#pragma once
#include <vector>
#include <string>

namespace lpd
{
	class Mesh;
	class MeshGroup;
	class AnimPose;

	class GLTFMeshLoader
	{
	public:
		LEOPARD_DLL MeshGroup* LoadMesh(const std::string& path) const;
		AnimPose* LoadSkeleton(const std::string& path) const;
	};
}
