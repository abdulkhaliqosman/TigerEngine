#pragma once

#include "animtrack.h"
#include <vector>
#include <string>
#include "animpose.h"

namespace lion
{
	struct Joint;

	struct JointTrack
	{
		int m_Id = -1;
		std::string m_Name;

		AnimTransformTrack m_TransformTrack;
	};

	class AnimPoseClip
	{
	public:
		void Sample(float time, AnimPose& outPose, float& outTime) const;
		float GetAdjustedTime(float time) const;

		int GetIndex(const std::string& id) const;
		void AddTrack(const JointTrack& track);

		inline JointTrack& GetTrack(int i) { return m_Tracks[i]; }

		inline float GetStartTime() { return m_StartTime; }
		inline float GetEndTime() { return m_EndTime; }
		inline bool GetLoop() { return m_Loop; }

		void SetStartTime(float value) { m_StartTime = value; }
		void SetEndTime(float value) { m_EndTime = value; }
		void SetLoop(bool value) { m_Loop = value; }

	private:
		JointIndexMap m_NameJointMap;
		std::vector<JointTrack> m_Tracks;

		float m_StartTime = 0.0f;
		float m_EndTime = 0.0f;
		bool m_Loop = false;

	};
}
