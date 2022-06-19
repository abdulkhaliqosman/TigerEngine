#pragma once

#include <jaguarcore\system\isystem.h>
#include <vector>
#include <string>
#include <jaguarcore/thread/jobsystem.h>

namespace lion
{
	class AnimationComponent;
	class AnimClip;
	class AnimPose;

	class AnimationJob : public jgr::Job
	{
	public:
		AnimationComponent* component;

		void Execute() override;
	};

	class AnimationSystem : public iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		AnimationComponent* CreateAnimationComponent();
		const AnimClip* LoadClip(const std::string& path);
		AnimPose* LoadPose(const std::string& path);
		AnimPose* ClonePose(const std::string& path);

		inline void SetJobSystem(jgr::JobSystem* jobSystem) { m_JobSystem = jobSystem; }

	private:
		std::vector<AnimationComponent*> m_AnimationComponents;
		std::vector<AnimClip*> m_AnimClips;
		std::vector<AnimPose*> m_AnimPoses;
		std::vector<AnimationJob*> m_Jobs;
		jgr::JobSystem* m_JobSystem;
	};
}