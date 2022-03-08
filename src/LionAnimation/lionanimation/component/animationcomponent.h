#pragma once
#include <jaguarcore/components/component.h>

namespace lion
{
	class AnimPose;
	class AnimClip;

	class AnimationComponent : public jgr::Component
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		inline void SetPose(AnimPose* pose) { m_Pose = pose; }

		void SetClip(const AnimClip* clip);

		void StartAnim();
		void PauseAnim();
		void StopAnim();

		inline void SetAnimSpeed(float speed) { m_Speed = speed; }
		inline void SetTimer(float time) { m_Timer = time; }
		inline void SetLoop(bool loop) { m_Loop = loop; }
	private:
		AnimPose* m_Pose = nullptr;
		const AnimClip* m_Clip = nullptr;

		bool m_IsPlaying = false;
		bool m_Loop = false;

		float m_Timer = 0.0f;
		float m_Speed = 1.0f;
	};
}