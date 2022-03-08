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
		MeshGroup* LoadMesh(const std::string& path) const;
	};
}
