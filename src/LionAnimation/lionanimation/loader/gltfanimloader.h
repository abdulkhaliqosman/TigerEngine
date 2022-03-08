#pragma once

#include <vector>
#include <string>

struct cgltf_data;

namespace lion
{
	class AnimClip;
	class AnimPose;

	class GLTFAnimLoader
	{
	public:
		~GLTFAnimLoader();

		void LoadFile(const std::string& path);
		void UnloadFile();

		std::vector<AnimClip*> LoadAnimClips() const;
		std::vector<AnimPose*> LoadPoses() const;

	private:
		cgltf_data* m_Data = nullptr;
		std::string m_Path;
	};
}
