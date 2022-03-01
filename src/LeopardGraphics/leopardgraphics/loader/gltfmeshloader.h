#pragma once
#include <vector>
#include <string>

namespace lpd
{
	class Mesh;
	class AnimPose;

	class GLTFMeshLoader
	{
	public:
		std::vector<Mesh*> LoadMesh(const std::string& path) const;
		AnimPose* LoadSkeleton(const std::string& path) const;
	};
}
