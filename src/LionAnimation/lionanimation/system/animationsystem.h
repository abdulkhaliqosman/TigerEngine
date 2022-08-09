#pragma once

#include <jaguarcore/thread/jobsystem.h>
#include <vector>
#include <string>

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

	class AnimationSystem : public iEngineSystem
	{
	public:
		inline AnimationSystem(iEngine& engine) : iEngineSystem(engine) {}
		inline ~AnimationSystem() {}

		void Setup() override;
		void Teardown() override;
		
		void StartScene() override;
		void StopScene() override;

		void Update() override;

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