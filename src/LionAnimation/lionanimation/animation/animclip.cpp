#include <lionanimation/lionpch.h>
#include "animclip.h"
#include "animpose.h"

#include <cmath>

namespace lion
{
	int AnimPoseClip::GetIndex(const std::string& str) const
	{
		auto it = m_NameJointMap.find(str);
		if (it == m_NameJointMap.end())
		{
			return Joint::INVALID_ID;
		}

		return it->second;
	}

	void AnimPoseClip::AddTrack(const JointTrack& track)
	{
		auto it = m_NameJointMap.find(track.m_Name);
		if (it != m_NameJointMap.end())
		{
			*(int*)nullptr;
		}

		int idx = m_Tracks.size();
		m_NameJointMap[track.m_Name] = idx;
		m_Tracks.push_back(track);
		m_Tracks.back().m_Id = idx;
	}

	void AnimPoseClip::Sample(float time, AnimPose& outPose, float& outTime) const
	{
		float adjustedTime = GetAdjustedTime(time);
		outTime = adjustedTime;
		// assert pose are the same

		size_t size = m_Tracks.size();

		for (int i = 0; i < size; ++i)
		{
			const JointTrack& jointTrack = m_Tracks[i];
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
	}

	float AnimPoseClip::GetAdjustedTime(float time) const
	{
		// we dont do rewinds
		if (time < 0.0f)
		{
			return 0.0f;
		}

		if (time <= m_EndTime)
		{
			return time;
		}

		if (!m_Loop)
		{
			return m_EndTime;
		}

		return fmodf(time, m_EndTime);
	}
}