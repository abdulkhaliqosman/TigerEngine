#pragma once

#include <vector>
#include <string>

struct cgltf_data;

namespace lion
{
	class AnimPoseClip;
	class AnimPose;

	class GLTFAnimLoader
	{
	public:
		~GLTFAnimLoader();

		void LoadFile(const std::string& path);
		void UnloadFile();

		std::vector<AnimPoseClip*> LoadAnimClips() const;
		AnimPose* LoadPose() const;

	private:
		cgltf_data* m_Data = nullptr;
	};
}
