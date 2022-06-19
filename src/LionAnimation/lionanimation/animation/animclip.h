#pragma once

#include "animtrack.h"
#include <vector>
#include <string>
#include "animpose.h"
#include <cassert>

namespace lion
{
	struct Joint;

	struct JointTrack
	{
		int m_Id = -1;
		std::string m_Name;

		AnimTransformTrack m_TransformTrack;
	};

	class AnimClip
	{
	public:
		void Sample(float time, AnimPose& outPose, float& outTime, bool loop) const;
		void Sample(float adjustedTime, AnimPose& outPose, const JointTrack& jointTrack) const;

		float GetAdjustedTime(float time, bool loop) const;

		int GetIndex(const std::string& id) const;
		void AddTrack(const JointTrack& track);

		inline JointTrack& GetTrack(int i) { assert(i >= 0 && i < m_Tracks.size()); return m_Tracks[i]; }

		inline float GetStartTime() { return m_StartTime; }
		inline float GetEndTime() { return m_EndTime; }

		void SetStartTime(float value) { m_StartTime = value; }
		void SetEndTime(float value) { m_EndTime = value; }

		inline const std::string& GetPath() const { return m_Path; }
		inline void SetPath(const std::string&path) { m_Path = path; }
	private:
		std::string m_Path;
		JointIndexMap m_NameJointMap;
		std::vector<JointTrack> m_Tracks;

		float m_StartTime = 0.0f;
		float m_EndTime = 0.0f;
	};
}
