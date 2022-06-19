#include <lionanimation/lionpch.h>
#include <lionanimation/animation/animclip.h>
#include <lionanimation/animation/animpose.h>

#include <cmath>
#include <cassert>
#include "optick.h"

namespace lion
{
	int AnimClip::GetIndex(const std::string& str) const
	{
		auto it = m_NameJointMap.find(str);
		if (it == m_NameJointMap.end())
		{
			return Joint::INVALID_ID;
		}

		return it->second;
	}

	void AnimClip::AddTrack(const JointTrack& track)
	{
		auto it = m_NameJointMap.find(track.m_Name);
		assert(it == m_NameJointMap.end());

		size_t idx = m_Tracks.size();
		m_NameJointMap[track.m_Name] = idx;
		m_Tracks.push_back(track);
		m_Tracks.back().m_Id = idx;
	}

	void AnimClip::Sample(float time, AnimPose& outPose, float& outTime, bool loop) const
	{
		OPTICK_EVENT();
		float adjustedTime = GetAdjustedTime(time, loop);
		outTime = adjustedTime;
		// assert pose are the same

		size_t size = m_Tracks.size();

		for (int i = 0; i < size; ++i)
		{
			Sample(adjustedTime, outPose, m_Tracks[i]);
		}
	}

	void AnimClip::Sample(float adjustedTime, AnimPose& outPose, const JointTrack& jointTrack) const
	{
		int jointId = outPose.GetIndex(jointTrack.m_Name);

		if (jointId != Joint::INVALID_ID)
		{
			Joint& joint = outPose.GetJoint(jointId);
			const AnimTransformTrack& track = jointTrack.m_TransformTrack;
			if (!track.positionTrack.Empty())
			{
				vec3 pos = track.positionTrack.GetValue(adjustedTime);
				joint.position = pos;
			}

			if (!track.rotationTrack.Empty())
			{
				quat rot = track.rotationTrack.GetValue(adjustedTime);
				joint.rotation = rot;
			}

			if (!track.scaleTrack.Empty())
			{
				vec3 scale = track.scaleTrack.GetValue(adjustedTime);
				joint.scale = scale;
			}
		}
	}

	float AnimClip::GetAdjustedTime(float time, bool loop) const
	{
		// we dont do rewinds
		if (time < m_StartTime)
		{
			return m_StartTime;
		}

		if (time <= m_EndTime)
		{
			return time;
		}

		if (!loop)
		{
			return m_EndTime;
		}

		return fmodf(time, m_EndTime);
	}
}