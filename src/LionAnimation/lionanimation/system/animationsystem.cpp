#include <lionanimation/lionpch.h>
#include <lionanimation/system/animationsystem.h>
#include <lionanimation/component/animationcomponent.h>
#include <lionanimation/loader/gltfanimloader.h>
#include "lionanimation/animation/animclip.h"
#include "lionanimation/animation/animpose.h"
#include "optick.h"

namespace lion
{
	void AnimationJob::Execute()
	{
		OPTICK_EVENT();
		component->Update();
	}

	void AnimationSystem::Startup()
	{
		for (auto* elem : m_AnimationComponents)
		{
			elem->Startup();
			auto* job = jgr::New<AnimationJob>();
			job->component = elem;
			m_Jobs.push_back(job);
		}
	}

	void AnimationSystem::Update()
	{
		OPTICK_EVENT();
		for (auto* elem : m_Jobs)
		{
			m_JobSystem->PushJob(elem);
		}
	}

	void AnimationSystem::Shutdown()
	{
		for (auto* elem : m_AnimationComponents)
		{
			jgr::Delete(elem);
		}

		for (auto* elem : m_AnimClips)
		{
			jgr::Delete(elem);
		}

		for (auto* elem : m_AnimPoses)
		{
			jgr::Delete(elem);
		}
	}

	AnimationComponent* AnimationSystem::CreateAnimationComponent()
	{
		AnimationComponent* animationComponent = jgr::New<AnimationComponent>();
		m_AnimationComponents.push_back(animationComponent);

		return animationComponent;
	}

	const AnimClip* AnimationSystem::LoadClip(const std::string& path)
	{
		for (auto* clip : m_AnimClips)
		{
			if (clip->GetPath() == path)
			{
				return clip;
			}
		}

		GLTFAnimLoader loader;
		loader.LoadFile(path);
		std::vector<AnimClip*> clips = loader.LoadAnimClips();
		m_AnimClips.insert(m_AnimClips.end(), clips.begin(), clips.end());

		return clips[0];
	}

	AnimPose* AnimationSystem::LoadPose(const std::string& path)
	{
		GLTFAnimLoader loader;
		loader.LoadFile(path);
		std::vector<AnimPose*> poses = loader.LoadPoses();

		m_AnimPoses.insert(m_AnimPoses.end(), poses.begin(), poses.end());

		return poses[0];
	}
}