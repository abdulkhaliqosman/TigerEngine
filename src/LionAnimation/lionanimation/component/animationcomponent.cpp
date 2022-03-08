#include <lionanimation/lionpch.h>
#include <lionanimation/component/animationcomponent.h>

#include <lionanimation/animation/animclip.h>
#include <lionanimation/animation/animpose.h>
#include "optick.h"

namespace lion
{
	void AnimationComponent::Startup()
	{
		float time;
		m_Clip->Sample(m_Timer, *m_Pose, time, false);
		m_Pose->ComputeGlobalTransforms();
	}

	void AnimationComponent::Update()
	{
		OPTICK_EVENT();
		// TODO: make a dT system

		if (m_IsPlaying)
		{
			m_Timer += 0.016666667f * m_Speed;

			float time;
			m_Clip->Sample(m_Timer, *m_Pose, time, m_Loop);
			m_Pose->ComputeGlobalTransforms();
		}
	}

	void AnimationComponent::Shutdown()
	{

	}

	void AnimationComponent::SetClip(const AnimClip* clip)
	{ 
		bool playing = m_IsPlaying;
		
		StopAnim();

		m_Clip = clip;

		if (playing)
		{
			StartAnim();
		}
	}

	void AnimationComponent::StartAnim()
	{
		m_IsPlaying = true;
	}

	void AnimationComponent::PauseAnim()
	{
		m_IsPlaying = false;
	}

	void AnimationComponent::StopAnim()
	{
		m_IsPlaying = false;
		m_Timer = 0.0f;
	}
}