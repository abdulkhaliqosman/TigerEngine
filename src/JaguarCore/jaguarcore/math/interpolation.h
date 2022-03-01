#pragma once
#include "quaternion.h"

namespace jgr
{
	namespace Math
	{
		template <typename T>
		T Clamp(const T& val, const T& min, const T& max)
		{
			return val < min ? min : (max < val ? max : val);
		}

		template <typename T, typename F>
		T Lerp(const T& p0, const T& p1, const F& t)
		{
			return (1 - t) * p0 + t * p1;
		}

		template <typename T, typename F>
		T Slerp(const T& q1, const T& q2, F t)
		{
			float quatdot = T::Dot(q1, q2);

			if (quatdot > 0.9995f)
			{
				T result = (1 - t) * q1 + t * q2;
				result.Normalize();
				return result;
			}

			T q2p = q2;
			if (quatdot < 0.0f) // far side
			{
				q2p = -q2;
				quatdot = T::Dot(q1, q2p);
			}

			float theta = acos(Clamp(quatdot, -1.0f, 1.0f));

			float sinTheta = sin(theta);
			float sintTheta = sin(t * theta);
			float sininvtTheta = sin((1 - t) * theta);

			return (sininvtTheta / sinTheta) * q1 + (sintTheta / sinTheta) * q2p;
		}


		inline quat Lerp(const quat& q1, const quat& q2, float t)
		{
			return Slerp(q1, q2, t);
		}

		// p0 and p3 are positions, p1 & p2 are anchor points
		template <typename T, typename F>
		T CubicBezier(const T& p0, const T& p1, const T& p2, const T& p3, const F& t)
		{
			return (1 - t) * (1 - t) * (1 - t) * p0
				+ 3 * (1 - t) * (1 - t) * t * p1
				+ 3 * (1 - t) * t * t * p2
				+ t * t * t * p3;
		}
	}
}