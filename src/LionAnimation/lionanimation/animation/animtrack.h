#pragma once
#include <vector>

namespace lion
{
	enum class InterpolationType
	{
		Invalid,
		Step,
		Linear,
		Cubic
	};

	template<typename T>
	struct AnimFrame
	{
		float time;
		T value;
	};

	using AnimFrameFloat = AnimFrame<float>;
	using AnimFrameVec3 = AnimFrame<vec3>;
	using AnimFrameQuat = AnimFrame<quat>;

	template<typename T>
	class AnimTrack
	{
	public:
		float StartTime() const
		{
			if (m_Track.size() == 0)
			{
				return 0.0f;
			}

			return m_Track[0].time;
		}

		float EndTime() const
		{
			if (m_Track.size() == 0)
			{
				return 0.0f;
			}

			return m_Track[m_Track.size() - 1].time;
		}

		void AddFrame(const AnimFrame<T>& frame) { m_Track.push_back(frame); }

		T GetValue(float time) const
		{
			if (Empty())
			{
				return T{};
			}

			if (m_Track.size() == 1)
			{
				return m_Track[0].value;
			}

			if (time < m_Track[0].time)
			{
				return m_Track[0].value;
			}

			// if higher than max use max
			if (time >= EndTime())
			{
				return m_Track[m_Track.size() - 1].value;
			}

			for (int i = 1; i < m_Track.size(); ++i)
			{
				if (time <= m_Track[i].time)
				{
					switch (m_InterpolationType)
					{
					case InterpolationType::Step:
					{
						return m_Track[i].value;
					}
					case InterpolationType::Linear:
					case InterpolationType::Cubic: // TODO: Actually implement cubic
					{
						float t = (time - m_Track[i - 1].time) / (m_Track[i].time - m_Track[i - 1].time);

						return jgr::Math::Lerp(m_Track[i - 1].value, m_Track[i].value, t);
					}

					}

				}
			}

			return T{};
		}

		bool Empty() const { return m_Track.size() == 0; }
		void SetInterpolationType(InterpolationType value) { m_InterpolationType = value; }

	private:
		std::vector<AnimFrame<T>> m_Track;
		InterpolationType m_InterpolationType;
	};

	using AnimTrackVec3 = AnimTrack<vec3>;
	using AnimTrackQuat = AnimTrack<quat>;


	struct AnimTransformTrack
	{
		AnimTrackVec3 positionTrack;
		AnimTrackQuat rotationTrack;
		AnimTrackVec3 scaleTrack;
	};
}